#pragma once

#include "CoreMinimal.h"
#include "git.h"

PROJECTACT_API DECLARE_LOG_CATEGORY_EXTERN(LogAct, Log, All);

#define FUNCTION_TCHAR (ANSI_TO_TCHAR(__FUNCTION__))
#define FILE_TCHAR (ANSI_TO_TCHAR(__FILE__))
#define COMMIT_HASH (ANSI_TO_TCHAR(COMMIT_HASH))

// git hash, 함수명과 라인 번호만 출력하는 간단한 로그
#define ACT_LOG(LogCategory, Verbosity, Format, ...) \
	UE_LOG(LogCategory, Verbosity, TEXT("[(%s)%s::%d] %s"), COMMIT_HASH, FUNCTION_TCHAR, __LINE__, *FString::Printf(Format, ##__VA_ARGS__))

// 파일이름(또는 파일 경로)까지 출력하는 전체 로그  
#define ACT_FULL_LOG(LogCategory, Verbosity, Format, ...) \
	UE_LOG(LogCategory, Verbosity, TEXT("[(%s)%s::%s::%d] %s"), COMMIT_HASH, FILE_TCHAR, FUNCTION_TCHAR, __LINE__, *FString::Printf(Format, ##__VA_ARGS__))

