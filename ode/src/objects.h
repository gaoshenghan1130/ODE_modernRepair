/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001,2002 Russell L. Smith.       *
 * All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file LICENSE.TXT.                                               *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file LICENSE-BSD.TXT.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
 *                                                                       *
 *************************************************************************/

 // object, body, and world structures.


#ifndef _ODE__PRIVATE_OBJECTS_H_
#define _ODE__PRIVATE_OBJECTS_H_


#include <ode/common.h>
#include <ode/memory.h>
#include <ode/mass.h>
#include <ode/objects.h>
#include "error.h"
#include "array.h"
#include "common.h"
#include "threading_base.h"
#include "odeou.h"


struct dxJointNode;
class dxStepWorkingMemory;
class dxWorldProcessContext;


// some body flags

enum {
    dxBodyFlagFiniteRotation = 1,  // use finite rotations
    dxBodyFlagFiniteRotationAxis = 2,  // use finite rotations only along axis
    dxBodyDisabled = 4,  // body is disabled
    dxBodyNoGravity = 8,  // body is not influenced by gravity
    dxBodyAutoDisable = 16, // enable auto-disable on body
    dxBodyLinearDamping = 32, // use linear damping
    dxBodyAngularDamping = 64, // use angular damping
    dxBodyMaxAngularSpeed = 128,// use maximum angular speed
    dxBodyGyroscopic = 256 // use gyroscopic term
};


// base class that does correct object allocation / deallocation

struct dBase {
    void *operator new (size_t size) { return dAlloc(size); }
    void *operator new (size_t, void *p) { return p; }
    void operator delete (void *ptr, size_t size) { dFree(ptr, size); }
    void *operator new[](size_t size) { return dAlloc(size); }
    void operator delete[](void *ptr, size_t size) { dFree(ptr, size); }
};


// base class for bodies and joints

struct dObject : public dBase {
    explicit dObject(dxWorld *w) : world(w), next(NULL), tome(NULL), tag(0), userdata(NULL) {}
    virtual ~dObject();

    dxWorld *world;		// world this object is in
    dObject *next;		// next object of this type in list
    dObject **tome;		// pointer to previous object's next ptr
    int tag;			// used by dynamics algorithms
    void *userdata;		// user settable data
};


// auto disable parameters
struct dxAutoDisable {
    dxAutoDisable() {}
    explicit dxAutoDisable(void *);

    dReal idle_time;		// time the body needs to be idle to auto-disable it
    int idle_steps;		// steps the body needs to be idle to auto-disable it
    unsigned int average_samples;     // size of the average_lvel and average_avel buffers
    dReal linear_average_threshold;   // linear (squared) average velocity threshold
    dReal angular_average_threshold;  // angular (squared) average velocity threshold
};


// damping parameters
struct dxDampingParameters {
    dxDampingParameters() {}
    explicit dxDampingParameters(void *);

    dReal linear_scale;  // multiply the linear velocity by (1 - scale)
    dReal angular_scale; // multiply the angular velocity by (1 - scale)
    dReal linear_threshold;   // linear (squared) average speed threshold
    dReal angular_threshold;  // angular (squared) average speed threshold
};


enum dxMarginalDeltaKind {
    MDK__MIN,

    MDK_EXTRA_ITERATIONS_REQUIREMENT_DELTA = MDK__MIN,
    MDK_PREMATURE_EXIT_DELTA,

    MDK__MAX,
};

// quick-step parameters
class dxQuickStepParameters
{
public:
    dxQuickStepParameters() {}
    explicit dxQuickStepParameters(void *);

private:
    dxQuickStepParameters(const dxQuickStepParameters &anotherInstance) { dIASSERT(false); } // disabled
    dxQuickStepParameters &operator =(const dxQuickStepParameters &anotherInstance) { dIASSERT(false); return *this; } // disabled

public:
    void AssignNumIterations(unsigned iterationCount)
    {
        dIASSERT(iterationCount != 0); // QuickStep implementation relies of number of iteration not being zero

        m_iterationCount = iterationCount;
        m_maxExtraIterationCount = DeriveExtraIterationCount(iterationCount, m_maxExtraIterationsFactor);
        UpdateDynamicIterationCountAdjustmentEnabledState();
    }

    unsigned GetNumIterations() const { return m_iterationCount; }

    void AssignPrematureExitDelta(dReal deltaValue)
    {
        dIASSERT(deltaValue >= 0);
        m_marginalDeltaValues[MDK_PREMATURE_EXIT_DELTA] = deltaValue;
        UpdateDynamicIterationCountAdjustmentEnabledState();
    }

    dReal GetPrematureExitDelta() const { return m_marginalDeltaValues[MDK_PREMATURE_EXIT_DELTA]; }

    void AssignExtraIterationsRequirementDelta(dReal deltaValue) { dIASSERT(deltaValue >= 0); m_marginalDeltaValues[MDK_EXTRA_ITERATIONS_REQUIREMENT_DELTA] = deltaValue; }
    dReal GetExtraIterationsRequirementDelta() const { return m_marginalDeltaValues[MDK_EXTRA_ITERATIONS_REQUIREMENT_DELTA]; }

    void AssignMaxNumExtraFactor(dReal maxNumExtraFactor)
    {
        dIASSERT(maxNumExtraFactor >= 0);

        m_maxExtraIterationsFactor = maxNumExtraFactor;
        m_maxExtraIterationCount = DeriveExtraIterationCount(m_iterationCount, maxNumExtraFactor);
        UpdateDynamicIterationCountAdjustmentEnabledState();
    }

    dReal GetMaxNumExtraFactor() const { return m_maxExtraIterationsFactor; }

    bool GetIsDynamicIterationCountAdjustmentEnabled() const { return m_dynamicIterationCountAdjustmentEnabled; }

    void AssignStatisticsSink(dWorldQuickStepIterationCount_DynamicAdjustmentStatistics *statistics) { m_statistics = statistics; }
    void ClearStatisticsSink() { m_statistics = &m_internal_statistics; }

    volatile atomicord32 *GetStatisticsIterationCountStorage() const { dSASSERT(sizeof(atomicord32) == membersize(dWorldQuickStepIterationCount_DynamicAdjustmentStatistics, iteration_count)); return _type_cast_union<atomicord32>(&m_statistics->iteration_count); }
    volatile atomicord32 *GetStatisticsPrematureExitsStorage() const { dSASSERT(sizeof(atomicord32) == membersize(dWorldQuickStepIterationCount_DynamicAdjustmentStatistics, premature_exits)); return _type_cast_union<atomicord32>(&m_statistics->premature_exits); }
    volatile atomicord32 *GetStatisticsProlongedExecutionsStorage() const { dSASSERT(sizeof(atomicord32) == membersize(dWorldQuickStepIterationCount_DynamicAdjustmentStatistics, prolonged_execs)); return _type_cast_union<atomicord32>(&m_statistics->prolonged_execs); }
    volatile atomicord32 *GetStatisticsFullExtraExecutionsStorage() const { dSASSERT(sizeof(atomicord32) == membersize(dWorldQuickStepIterationCount_DynamicAdjustmentStatistics, full_extra_execs)); return _type_cast_union<atomicord32>(&m_statistics->full_extra_execs); }

private:
    static unsigned DeriveExtraIterationCount(unsigned iterationCount, dReal extraIterationCountFactor)
    {
        dIASSERT(iterationCount != 0);
        dIASSERT(extraIterationCountFactor >= 0);

        dReal extraIterationCount = iterationCount * extraIterationCountFactor;
        return extraIterationCount < UINT_MAX ? (unsigned)extraIterationCount : UINT_MAX;
    }

    void UpdateDynamicIterationCountAdjustmentEnabledState()
    {
        m_dynamicIterationCountAdjustmentEnabled = m_maxExtraIterationCount != 0 || m_marginalDeltaValues[MDK_PREMATURE_EXIT_DELTA] != 0;
    }

public:
    unsigned int m_iterationCount;         // number of SOR iterations to perform
    unsigned int m_maxExtraIterationCount; // maximal number of extra iterations that can be performed until maximal delta falls below the upper margin
    dReal m_maxExtraIterationsFactor;      // factor of maximal extra iteration count with respect to standard iteration count
    dReal m_marginalDeltaValues[MDK__MAX]; // marginal values for LCP iteration maximal delta
    bool m_dynamicIterationCountAdjustmentEnabled;
    dWorldQuickStepIterationCount_DynamicAdjustmentStatistics *m_statistics; // Adjustment statistics (the internal one or an externally assigned)
    dReal w;                               // the SOR over-relaxation parameter

private:
    dWorldQuickStepIterationCount_DynamicAdjustmentStatistics m_internal_statistics; // The internal statistics is used to not have to check m_statistics for NULL; the local instance is used instead of a global one to avoid cache line conflicts between different threads possibly serving separate worlds.
};


// contact generation parameters
struct dxContactParameters {
    dxContactParameters() {}
    explicit dxContactParameters(void *);

    dReal max_vel;		// maximum correcting velocity
    dReal min_depth;		// thickness of 'surface layer'
};

// position vector and rotation matrix for geometry objects that are not
// connected to bodies.
struct dxPosR {
    dVector3 pos;
    dMatrix3 R;
};

struct dxBody : public dObject {
    dxBody(dxWorld *w);

    dxJointNode *firstjoint;	// list of attached joints
    unsigned flags;			// some dxBodyFlagXXX flags
    dGeomID geom;			// first collision geom associated with body
    dMass mass;			// mass parameters about POR
    dMatrix3 invI;		// inverse of mass.I
    dReal invMass;		// 1 / mass.mass
    dxPosR posr;			// position and orientation of point of reference
    dQuaternion q;		// orientation quaternion
    dVector3 lvel, avel;		// linear and angular velocity of POR
    dVector3 facc, tacc;		// force and torque accumulators
    dVector3 finite_rot_axis;	// finite rotation axis, unit length or 0=none

    // auto-disable information
    dxAutoDisable adis;		// auto-disable parameters
    dReal adis_timeleft;		// time left to be idle
    int adis_stepsleft;		// steps left to be idle
    dVector3* average_lvel_buffer;      // buffer for the linear average velocity calculation
    dVector3* average_avel_buffer;      // buffer for the angular average velocity calculation
    unsigned int average_counter;      // counter/index to fill the average-buffers
    int average_ready;            // indicates ( with = 1 ), if the Body's buffers are ready for average-calculations

    void(*moved_callback)(dxBody*); // let the user know the body moved
    dxDampingParameters dampingp; // damping parameters, depends on flags
    dReal max_angular_speed;      // limit the angular velocity to this magnitude
};


struct dxWorld : public dBase, public dxThreadingBase, private dxIThreadingDefaultImplProvider {
public:
    dxWorld();
    virtual ~dxWorld(); // Compilers issue warnings if a class with virtual methods does not have a virtual destructor :(

    void assignThreadingImpl(const dxThreadingFunctionsInfo *functions_info, dThreadingImplementationID threading_impl);

    unsigned calculateIslandIterationMaxThreadCount(unsigned *ptrOut_activeThreadCount = NULL) const
    {
        unsigned activeThreadCount, *ptrActiveThreadCountToUse = ptrOut_activeThreadCount != NULL ? &activeThreadCount : NULL;
        unsigned limitedCount = calculateThreadingLimitedThreadCount(islands_max_threads, false, ptrActiveThreadCountToUse);
        if (ptrOut_activeThreadCount != NULL) {
            *ptrOut_activeThreadCount = dMACRO_MAX(activeThreadCount, 1U);
        }
        return dMACRO_MAX(limitedCount, 1U);
    }

    unsigned calculatePerIslandSteppingMaxThreadCount() const
    {
        unsigned limitedCount = calculateThreadingLimitedThreadCount(stepping_max_threads, false);
        return dMACRO_MAX(limitedCount, 1U);
    }

    unsigned calculatePerIslandSolvingMaxThreadCount() const
    {
        unsigned limitedCount = calculateThreadingLimitedThreadCount(solving_max_threads, false);
        return dMACRO_MAX(limitedCount, 1U);
    }

    dxWorldProcessContext *unsafeGetWorldProcessingContext() const;

private: // dxIThreadingDefaultImplProvider
    virtual const dxThreadingFunctionsInfo *retrieveThreadingDefaultImpl(dThreadingImplementationID &out_defaultImpl);

public:
    dxBody *firstbody;		// body linked list
    dxJoint *firstjoint;		// joint linked list
    int nb, nj;			// number of bodies and joints in lists
    dVector3 gravity;		// gravity vector (m/s/s)
    dReal global_erp;		// global error reduction parameter
    dReal global_cfm;		// global constraint force mixing parameter
    dxAutoDisable adis;		// auto-disable parameters
    int body_flags;               // flags for new bodies
    unsigned islands_max_threads; // maximum threads to allocate for island processing
    unsigned stepping_max_threads; // maximum threads to allocate for stepping each island
    unsigned solving_max_threads; // maximum threads to allocate for solving equation systems
    dxStepWorkingMemory *wmem; // Working memory object for dWorldStep/dWorldQuickStep

    dxQuickStepParameters qs;
    dxContactParameters contactp;
    dxDampingParameters dampingp; // damping parameters
    dReal max_angular_speed;      // limit the angular velocity to this magnitude

    void* userdata;
};


#endif // #ifndef _ODE__PRIVATE_OBJECTS_H_
