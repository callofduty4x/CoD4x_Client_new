#include <cstddef>
#include "../q_shared.h"
#include "ode/include/ode/objects.h"
#include "ode/src/joint.h"
#include "phys_internal.h"
#include "../common/com_debug.h"


void Phys_AxisToOdeMatrix3(const float *inAxis, float *outMatrix)
{
  int i;

  for ( i = 0; i != 3; ++i )
  {
    outMatrix[0] = inAxis[0];
    outMatrix[1] = inAxis[3];
    outMatrix[2] = inAxis[6];
    outMatrix[3] = 0.0;
    outMatrix += 4;
    inAxis++;
  }
}


dxJointAMotor * Phys_CreateAngularMotor(PhysWorld worldIndex, int obj1, int obj2, int numAxes, const float (*axes)[3], const float *motorSpeeds, const float *motorFMaxs, const float *lowStops, const float *highStops)
{
    dxJointAMotor *amotor;
    dxJointAMotor *joint;

    assert(numAxes >= 0 && numAxes <= 3);

    amotor = physGlob.aMotorArray.allocate();
    if ( !amotor )
    {
        Com_PrintWarning(CON_CHANNEL_PHYS, "Physics: Out of angular motor joints (%d max)\n", physGlob.aMotorArray.getMaxEntryCount());
        return nullptr;
    }
    joint = static_cast<dxJointAMotor*>(dJointCreateAMotor(physGlob.world[worldIndex], amotor));
    if ( !joint )
    {
        return nullptr;
    }
    dJointAttach(joint, (dxBody *)obj1, (dxBody *)obj2);
    dJointSetAMotorMode(joint, 1);
    dJointSetAMotorNumAxes(joint, 3);

    dJointSetAMotorAxis(joint, 2, obj2 ? 2 : 0, axes[2][0], axes[2][1], axes[2][3]);
    dJointSetAMotorAxis(joint, 0, obj1 != 0, axes[0][0], axes[0][1], axes[0][2]);
    Phys_SetAngularMotorParams(worldIndex, (int)joint, motorSpeeds, motorFMaxs, lowStops, highStops);
    return joint;
}


dxJointHinge* Phys_CreateHinge(
        PhysWorld worldIndex,
        int obj1,
        int obj2,
        const float *anchor,
        const float *axis,
        float motorSpeed,
        float motorMaxForce,
        float lowStop,
        float highStop)
{
    dxJointHinge *hinge;
    dxJointHinge *joint;

    hinge = physGlob.hingeArray.allocate();

    if ( !hinge )
    {
        Com_PrintWarning(CON_CHANNEL_PHYS, "Physics: Out of hinge joints (%d max)\n", physGlob.hingeArray.getMaxEntryCount());
        return nullptr;
    }
    else
    {
        joint = static_cast<dxJointHinge*>(dJointCreateHinge(physGlob.world[worldIndex], hinge));
        if ( joint )
        {
            dJointAttach(joint, (dxBody *)obj1, (dxBody *)obj2);
            dJointSetHingeAnchor(joint, *anchor, anchor[1], anchor[2]);
            dJointSetHingeAxis(joint, *axis, axis[1], axis[2]);
            Phys_SetHingeParams(worldIndex, (int)joint, motorSpeed, motorMaxForce, lowStop, highStop);
        }
        return joint;
    }
}

dxJoint * Phys_CreateBallAndSocket(PhysWorld worldIndex, int obj1, int obj2, const float *anchor)
{
    dxJointBall *ball;
    dxJointBall *joint;

    ball = physGlob.ballArray.allocate();

    if ( !ball )
    {
        Com_PrintWarning(CON_CHANNEL_PHYS, "Physics: Out of ball and socket joints (%d max)\n", physGlob.ballArray.getMaxEntryCount());
        return nullptr;
    }
    else
    {
        joint = static_cast<dxJointBall*>(dJointCreateBall(physGlob.world[worldIndex], ball));
        if ( joint )
        {
            dJointAttach(joint, (dxBody *)obj1, (dxBody *)obj2);
            dJointSetBallAnchor(joint, anchor[0], anchor[1], anchor[2]);
        }
        return joint;
    }
}

void Phys_InitJoints()
{
  physGlob.hingeArray.init( );
  physGlob.ballArray.init( );
  physGlob.aMotorArray.init( );
}

void Phys_JointDestroy(PhysWorld worldIndex, int id)
{
    assert(id);
    dJointDestroy((dxJoint *)id);

    if(physGlob.hingeArray.isMember(id))
    {
        physGlob.hingeArray.release((dxJointHinge *)id);
        return;
    }

    if(physGlob.ballArray.isMember(id))
    {
        physGlob.ballArray.release((dxJointBall *)id);
        return;
    }

    if(physGlob.aMotorArray.isMember(id))
    {
        physGlob.aMotorArray.release((dxJointAMotor *)id);
        return;
    }
    assertx(0, "Phys_JointDestroy: Tried to destroy joint of unknown type");
}
