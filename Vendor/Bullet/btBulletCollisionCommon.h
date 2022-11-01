/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2006 Erwin Coumans  https://bulletphysics.org

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BULLET_COLLISION_COMMON_H
#define BULLET_COLLISION_COMMON_H

///Common headerfile includes for Bullet Collision Detection

///Bullet's btCollisionWorld and btCollisionObject definitions
#include <Vendor/Bullet/BulletCollision/CollisionDispatch/btCollisionWorld.h>
#include <Vendor/Bullet/BulletCollision/CollisionDispatch/btCollisionObject.h>

///Collision Shapes
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btBoxShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btSphereShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btCapsuleShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btCylinderShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btConeShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btStaticPlaneShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btTriangleMesh.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btScaledBvhTriangleMeshShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btTriangleMeshShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btTriangleIndexVertexArray.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btCompoundShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btTetrahedronShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btEmptyShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btMultiSphereShape.h>
#include <Vendor/Bullet/BulletCollision/CollisionShapes/btUniformScalingShape.h>

///Narrowphase Collision Detector
#include <Vendor/Bullet/BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h>

//#include <Vendor/Bullet/BulletCollision/CollisionDispatch/btSphereBoxCollisionAlgorithm.h>
#include <Vendor/Bullet/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h>

///Dispatching and generation of collision pairs (broadphase)
#include <Vendor/Bullet/BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <Vendor/Bullet/BulletCollision/BroadphaseCollision/btSimpleBroadphase.h>
#include <Vendor/Bullet/BulletCollision/BroadphaseCollision/btAxisSweep3.h>
#include <Vendor/Bullet/BulletCollision/BroadphaseCollision/btDbvtBroadphase.h>

///Math library & Utils
#include <Vendor/Bullet/LinearMath/btQuaternion.h>
#include <Vendor/Bullet/LinearMath/btTransform.h>
#include <Vendor/Bullet/LinearMath/btDefaultMotionState.h>
#include <Vendor/Bullet/LinearMath/btQuickprof.h>
#include <Vendor/Bullet/LinearMath/btIDebugDraw.h>
#include <Vendor/Bullet/LinearMath/btSerializer.h>

#endif  //BULLET_COLLISION_COMMON_H
