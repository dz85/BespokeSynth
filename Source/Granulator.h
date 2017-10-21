//
//  Granulator.h
//  modularSynth
//
//  Created by Ryan Challinor on 9/12/13.
//
//

#ifndef __modularSynth__Granulator__
#define __modularSynth__Granulator__

#include <iostream>
#include "Ramp.h"

#define MAX_GRAINS 16

class ChannelBuffer;

class Grain
{
public:
   Grain() : mPos(0), mSpeed(0), mVol(0), mStereoPosition(0) {}
   void Spawn(double time, float pos, float speed, float lengthInMs, float vol);
   void Process(double time, ChannelBuffer* buffer, int bufferLength, float* output);
   void DrawGrain(int idx, float x, float y, float w, float h, int bufferStart, int bufferLength, bool wrapAround);
   void Clear() { mVol = 0; }
private:
   float GetWindow(double time);
   float mPos;
   float mSpeed;
   double mStartTime;
   double mEndTime;
   float mVol;
   float mStereoPosition;
};

class Granulator
{
public:
   Granulator();
   void Process(double time, ChannelBuffer* buffer, int bufferLength, float offset, float* output);
   void Draw(float x, float y, float w, float h, int bufferStart, int bufferLength, bool wrapAround = true);
   void Reset();
   void ClearGrains();
   void SetLiveMode(bool live) { mLiveMode = live; }
   
   float mSpeed;
   float mGrainLengthMs;
   float mGrainSpacing;
   float mPosRandomizeMs;
   float mSpeedRandomize;
   float mSpacingRandomize;
   bool mOctaves;
   
private:
   void SpawnGrain(double time, float offset);
   
   double mLastGrainSpawnMs;
   int mNextGrainIdx;
   Grain mGrains[MAX_GRAINS];
   bool mLiveMode;
};

#endif /* defined(__modularSynth__Granulator__) */
