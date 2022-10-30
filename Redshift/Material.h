#ifndef RSH_MATERIAL_H
#define RSH_MATERIAL_H

#include <Redshift/Types.h>

///////////////////////////////////////////////////////////
// Material definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class Material
  {
  public:
    inline R32V3 const& GetDiffuseColor() const { return mDiffuseColor; }
    inline R32V3 const& GetSpecularColor() const { return mSpecularColor; }
    inline R32V3 const& GetReflectionColor() const { return mReflectionColor; }
    inline R32V3 const& GetAmbientColor() const { return mAmbientColor; }
    inline R32V3 const& GetEmissiveColor() const { return mEmissiveColor; }

    inline R32 GetDiffuseFactor() const { return mDiffuseFactor; }
    inline R32 GetSpecularFactor() const { return mSpecularFactor; }
    inline R32 GetReflectionFactor() const { return mReflectionFactor; }
    inline R32 GetShininess() const { return mShininess; }
    inline R32 GetShininessExponent() const { return mShininessExponent; }
    inline R32 GetAmbientFactor() const { return mAmbientFactor; }
    inline R32 GetBumpFactor() const { return mBumpFactor; }
    inline R32 GetEmissiveFactor() const { return mEmissiveFactor; }

  public:
    inline void SetDiffuseColor(R32V3 color) { mDiffuseColor = color; }
    inline void SetSpecularColor(R32V3 color) { mSpecularColor = color; }
    inline void SetReflectionColor(R32V3 color) { mReflectionColor = color; }
    inline void SetAmbientColor(R32V3 color) { mAmbientColor = color; }
    inline void SetEmissiveColor(R32V3 color) { mEmissiveColor = color; }

    inline void SetDiffuseFactor(R32 value) { mDiffuseFactor = value; }
    inline void SetSpecularFactor(R32 value) { mSpecularFactor = value; }
    inline void SetReflectionFactor(R32 value) { mReflectionFactor = value; }
    inline void SetShininess(R32 value) { mShininess = value; }
    inline void SetShininessExponent(R32 value) { mShininessExponent = value; }
    inline void SetAmbientFactor(R32 value) { mAmbientFactor = value; }
    inline void SetBumpFactor(R32 value) { mBumpFactor = value; }
    inline void SetEmissiveFactor(R32 value) { mEmissiveFactor = value; }

  private:
    R32V3 mDiffuseColor{};
    R32V3 mSpecularColor{};
    R32V3 mReflectionColor{};
    R32V3 mAmbientColor{};
    R32V3 mEmissiveColor{};

    R32 mDiffuseFactor{};
    R32 mSpecularFactor{};
    R32 mReflectionFactor{};
    R32 mShininess{};
    R32 mShininessExponent{};
    R32 mAmbientFactor{};
    R32 mBumpFactor{};
    R32 mEmissiveFactor{};
  };
}

#endif