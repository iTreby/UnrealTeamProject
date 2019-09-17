// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef TEAMPROJECT_TeamProjectCharacter_generated_h
#error "TeamProjectCharacter.generated.h already included, missing '#pragma once' in TeamProjectCharacter.h"
#endif
#define TEAMPROJECT_TeamProjectCharacter_generated_h

#define TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_RPC_WRAPPERS
#define TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesATeamProjectCharacter(); \
	friend struct Z_Construct_UClass_ATeamProjectCharacter_Statics; \
public: \
	DECLARE_CLASS(ATeamProjectCharacter, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/TeamProject"), NO_API) \
	DECLARE_SERIALIZER(ATeamProjectCharacter)


#define TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_INCLASS \
private: \
	static void StaticRegisterNativesATeamProjectCharacter(); \
	friend struct Z_Construct_UClass_ATeamProjectCharacter_Statics; \
public: \
	DECLARE_CLASS(ATeamProjectCharacter, ACharacter, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/TeamProject"), NO_API) \
	DECLARE_SERIALIZER(ATeamProjectCharacter)


#define TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATeamProjectCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATeamProjectCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATeamProjectCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATeamProjectCharacter); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATeamProjectCharacter(ATeamProjectCharacter&&); \
	NO_API ATeamProjectCharacter(const ATeamProjectCharacter&); \
public:


#define TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ATeamProjectCharacter(ATeamProjectCharacter&&); \
	NO_API ATeamProjectCharacter(const ATeamProjectCharacter&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATeamProjectCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATeamProjectCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATeamProjectCharacter)


#define TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__CameraBoom() { return STRUCT_OFFSET(ATeamProjectCharacter, CameraBoom); } \
	FORCEINLINE static uint32 __PPO__FollowCamera() { return STRUCT_OFFSET(ATeamProjectCharacter, FollowCamera); }


#define TeamProject_Source_TeamProject_TeamProjectCharacter_h_9_PROLOG
#define TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_RPC_WRAPPERS \
	TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_INCLASS \
	TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_PRIVATE_PROPERTY_OFFSET \
	TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_INCLASS_NO_PURE_DECLS \
	TeamProject_Source_TeamProject_TeamProjectCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> TEAMPROJECT_API UClass* StaticClass<class ATeamProjectCharacter>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TeamProject_Source_TeamProject_TeamProjectCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
