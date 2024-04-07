#pragma once
#include "EncryptValue.h"
#include "ioHashString.h"
#include <vector>
#include <list>



class ioSkill
{
public:
	struct ScreenBlindTime
	{
		DWORD m_dwUpTime;
		DWORD m_dwCenterTime;
		DWORD m_dwDownTime;
	};

	struct ScreenBlindSetting
	{
		int m_iMaxAlpha;
		DWORD m_dwColor;
	};


	enum SkillCharColType
	{
		SCCT_NONE,
		SCCT_ALL,
		SCCT_TEAM,
	};
	enum ObjEnableType
	{
		OET_NONE,
		OET_TYPE1,
	};

	typedef std::vector< ioHashString > ioHashStringVec;

	struct AniRotateInfo
	{
		DWORD m_dwTime;
		float m_fAngle;

		AniRotateInfo()
		{
			m_dwTime = 0;
			m_fAngle = 0.0f;
		}
	};
	typedef std::vector<AniRotateInfo> vAniRotateInfoList;
	struct ExtraAniJump
	{
		DWORD m_dwTime;
		float m_fPower;

		ExtraAniJump()
		{
			m_dwTime = 0;
			m_fPower = 0.0f;
		}
	};

	typedef std::vector<ExtraAniJump> vExtraAniJumpList;


	enum DefenseBreakType
	{
		DBT_NONE,
		DBT_NORMAL,
		DBT_ALL,
		DBT_CHANGE,
		DBT_MAX,
	};
public:
	char szBuf[4]; //버퍼추가
	ioHashString m_GroupName;
	ioHashString m_TitleName;

	ioHashString m_Name;
	ioHashString m_DescName;
	ioHashString m_DescFullName;
	ioHashString m_Desc;
	ioHashString m_DescBubble;

	int m_SkillUseType;

	DWORD m_dwWeaponBaseIndex;
	DWORD m_dwDescBubbleDuration;

	// camera
	ioHashString m_CameraBuff;

	// Normal
	ioHashString m_SkillMotionName; //여긴 OK
	float m_fAnimationTimeRate;

	int  m_ProtectCancelType;
	CEncrypt<bool> m_bDisableSkillProtect;
	bool m_bPreDelayProtect;

	ioHashString m_PreDelayAnimation; //여긴 OK
	DWORD m_dwPreDelayTime;
	DWORD m_dwAnimationEndDelay; //추가

	ioHashString m_PreDelayOwnerEffect;
	ioHashString m_PreDelayOtherEffect;

	// Down
	ioHashString m_DownSkillMotionName;
	float m_fDownAnimationTimeRate;

	bool m_bDownPreDelayProtect;
	ioHashString m_DownPreDelayAnimation;
	DWORD m_dwDownPreDelayTime;

	ioHashString m_DownPreDelayOwnerEffect;
	ioHashString m_DownPreDelayOtherEffect;

	// Jump
	ioHashString m_JumpSkillMotionName;
	float m_fJumpAnimationTimeRate;

	bool m_bJumpPreDelayProtect;
	ioHashString m_JumpPreDelayAnimation;
	DWORD m_dwJumpPreDelayTime;

	ioHashString m_JumpPreDelayOwnerEffect;
	ioHashString m_JumpPreDelayOtherEffect;

	ioHashString m_PreDelayEffect;
	ioHashString m_SkillEffectName;
	ioHashString m_IconName;
	ioHashString m_SkillTextImage;
	ioHashString m_SkillEndEffectName;
	ioHashString m_SkillSoundName;
	DWORD m_SkillSoundID;

	ioHashString m_SkillMapEffectName;
	DWORD m_dwSkillMapEffect;

	DWORD m_dwPreDelayStartTime;
	DWORD m_dwFireMotionEndTime;

	//여기까진 OK

	ScreenBlindTime m_ScreenBlindTime; //ok

	//여기 뭐가 추가됨

	bool m_bUseCustomBlind;
	ScreenBlindSetting m_SkillBlind;

	CEncrypt<float> m_fNeedGauge;
	CEncrypt<float> m_fFireDecreaseGauge;

	DWORD m_dwCameraEvent;

	void* m_pOwnerItem;
	CEncrypt<DWORD> m_dwMotionStartTime; //이거 못가져옴
	DWORD m_dwMotionEndTime;
	DWORD m_dwEnableReserveTime;

	bool m_bUseAutoTargetValue;
	bool m_bAutoTargetDownState;
	float m_fAutoTargetMinAngle;
	float m_fAutoTargetMaxAngle;
	float m_fAutoTargetRange;

	CEncrypt<int> m_iSkillType;
	CEncrypt<int> m_iSubSkillType;

	bool m_bReduceGauge;
	SkillCharColType m_EnableCharCollisionSkip;

	DWORD m_dwSwitchSkill;
	DWORD m_dwEnableSwitchTime;

	DWORD m_dwSemiSwitchSkill;
	DWORD m_dwEnableSemiSwitchTime;

	// For Growth
	float m_fExtraAniRate;

	// For JumpingSkill
	CEncrypt<bool> m_bUseOnlyJumpping;
	CEncrypt<bool> m_bEnableJumpingSkill;
	CEncrypt<bool> m_bEnableJumpingSkillOnBlowWound;
	CEncrypt<float> m_fEnableJumpingSkillMaxHeight;

	// For DownSkill
	CEncrypt<bool> m_bUseOnlyDown;
	CEncrypt<bool> m_bEnableDownSkill;

	// For BlowWoundSkill
	CEncrypt<bool> m_bEnableBlowWoundSkill;
	CEncrypt<bool> m_bNoCheckDropSpeed;
	CEncrypt<float> m_fEnableBlowWoundSkillHeight;
	CEncrypt<float> m_fEnableBlowWoundSkillMaxHeight;

	// For Skill End Next Jump
	float m_fSkillEndNextJumpAmt;
	float m_fSkillEndNextLandRate;

	// For Wound Skill
	CEncrypt<bool> m_bEnableWoundSkill;

	// For IceState Skill
	CEncrypt<bool> m_bEnableIceStateSkill;

	// for flamestate(buff) skill
	CEncrypt<bool> m_bEnableIFlameStateBuff;
	ioHashStringVec m_bEnableFlameStateBuffList;

	CEncrypt<bool> m_bInitJumpPower;
	CEncrypt<bool> m_bCircleNoChangeY;

	// For SKill Move
	CEncrypt<float> m_fSkillMoveRate;

	bool m_bNoChangeFallState;
	bool m_bHideEquipItemByRotationWeapon;

	// For Gravity
	CEncrypt<float> m_fSkillGravityRate;
	CEncrypt<float> m_fSkillGravityDownRate;
	CEncrypt<float> m_fSkillGravityJumpRate;

	// For Ani Rotate
	vAniRotateInfoList m_vAniRotateInfoList;

	int m_iCurAniRotate;
	DWORD m_dwAniRotateTime;
	float m_fAniRotateAngle;

	// 
	ioHashString m_OwnerSkillStartBuff;
	ioHashString m_OwnerSkillEndBuff;
	ioHashString m_AutoStartBuff;

	// ZeroHP, Boss, King
	CEncrypt<bool> m_bDisableZeroHPSkill;
	CEncrypt<bool> m_bDisableBossSkill;
	CEncrypt<bool> m_bDisableKingSkill;
	CEncrypt<bool> m_bDisableFootballSkill;
	CEncrypt<bool> m_bDisableGangSiModeSkill;
	CEncrypt<int> m_iDisableWeaponTypeSkill;

	// limit hp rate
	CEncrypt<bool> m_bUseLimitHP;
	CEncrypt<float> m_fLimitHPRate;

	// Grappling
	char m_SkillGrapplingInfo[92];
	bool m_bChangeGrapplingTargetPos;

	// Hide skill desc
	CEncrypt<bool> m_bHideSkillDesc;

	CEncrypt<float> m_fPassiveSkillGaugeRate;
public:
	CEncrypt<float> m_fCurChargeRate;

	CEncrypt<float> m_fMaxDamageRate;
	CEncrypt<float> m_fMaxForceRate;
	CEncrypt<float> m_fMaxBlowRate;

	CEncrypt<float> m_fMaxRangeRate;
	CEncrypt<float> m_fMaxSpeedRate;
	CEncrypt<float> m_fMaxChargeAniRate;
	CEncrypt<float> m_fMaxForceSlidingRate;

	CEncrypt<float> m_fMaxTargetRangeRate;
	CEncrypt<float> m_fMaxTargetAngleRate;

	CEncrypt<float> m_fMaxFloatRate;

	CEncrypt<float> m_fMaxScaleRate;
	CEncrypt<float> m_fMaxExplosionRate;

	CEncrypt<float> m_fMaxLiveTimeRate;
	CEncrypt<float> m_fMaxWoundedTimeRate;

	CEncrypt<float> m_fMaxBuffLiveTimeRate;

	ObjEnableType   m_nEnableObjitemSkillType;

public:
	float m_fAirJumpPower;
	float m_fAirForcePower;
	float m_fAirJumpPowerRate;

	std::list<float> m_vAirJumpTimeList;
	int m_iCurAirJump;

	// For ExtraAniJump
	DWORD m_dwExtraAniJumpTime;
	float m_fExtraAniJumpPower;

	int m_iCurExtraAniJump;
	vExtraAniJumpList m_vExtraAniJumpList;

	// For Dir Skill
	CEncrypt<bool> m_bChangeDirRot;
	CEncrypt<bool> m_bEnableDirRotNormalSkill;
	CEncrypt<bool> m_bEnableDirRotJumpSkill;
	CEncrypt<bool> m_bEnableDirRotDownSkill;

	// For Speed Skill
	CEncrypt<bool> m_bInitMoveSpeedNormalSkill;
	CEncrypt<bool> m_bInitMoveSpeedJumpSkill;
	CEncrypt<bool> m_bInitMoveSpeedDownSkill;

	DefenseBreakType m_eDefenseSkillBreakType;

	// For Skill Cancel Skill
	CEncrypt<bool> m_bEnableCancelBySkill;
	CEncrypt<DWORD> m_dwEnableCancelBySkillTime;
	CEncrypt<DWORD> m_dwSkillStartTime; //이거 못가져온다.

	// For ActiveCount
	CEncrypt<int>  m_iMaxActiveCount;
	int            m_iCurActiveCount;
public:
	ioHashString m_HandMesh;
	bool m_bUseItemMesh;
	bool m_bVisibleEquipMesh;

	bool m_bSetHandMesh;
public:
	ioHashStringVec	m_ExBuffList;
	CEncrypt<bool> m_bExBuffHPZero;

public:
	bool m_bPetForceHide;

public:
	bool m_bEnableThunderBirdHoldUseSkill;

	bool m_bNoCheckFallState;
	bool m_bSwitchSkillEndJump;
	bool m_bNoCheckSkillmotion;

public:
	bool IsSkillStart();
	DWORD GetSkillWaitTime();
	bool IsTimeGateWeaponSkill();
	bool IsBrujoHelmetSkill(); //요술사 서클릿
};

