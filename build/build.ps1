### CONFIG #####################################################################

# 프로젝트 이름 및 버전
$projectName = "Qkcolb"
$projectVersionMajor = 0
$projectVersionMinor = 1

# 프로젝트 root
# 한글 시발 => https://torbjorn.tistory.com/550#:~:text=%EA%B4%80%EB%A6%AC%EC%9E%90%20%EC%98%B5%EC%85%98%20%ED%83%AD%EC%97%90%EC%84%9C%20%EC%9C%A0%EB%8B%88,%EB%82%98%EC%98%A4%EB%8A%94%20%EA%B2%83%EC%9D%84%20%ED%99%95%EC%9D%B8%ED%95%A0%20%EC%88%98%20%EC%9E%88%EC%8A%B5%EB%8B%88%EB%8B%A4.
# $projectRoot = "C:/Users/김완수/Documents/Study/blockchain"
$projectRoot = ".."

# 빌드 형상(Configuration)
$buildType = ""

# 빌드 대상 바이너리 파일명 및 소스파일 목록
$outputFileName = "$projectName-$projectVersionMajor.$projectVersionMinor.exe"
$srcFiles =
    "$projectRoot/src/main.cpp",
    "$projectRoot/src/Block.cpp",
    "$projectRoot/src/sha256.cpp"

# 공통 컴파일러
$cxxCompiler = "C:/mingw64/bin/g++.exe"

# 공통 헤더 파일 Include 디렉토리(-I)
$includeDirectories = "$projectRoot/include"

# 공통 컴파일 옵션, 링크 옵션
$compileOption = "-Wall -std=c++17"
$linkOption = ""

# 공통 링크 라이브러리(-l)
$linkLibraries = ""

# 공통 링크 라이브러리 디렉토리(-L)
$linkDirectories = ""

# "Debug" 형상 한정 컴파일 옵션, 링크 옵션
$cxxFlagsDebug = "-DDEBUG"
$exeLinkerFlagsDebug = ""

# "Release" 형상 한정 컴파일 옵션, 링크 옵션
$cxxFlagsRelease = ""
$exeLinkerFlagsRelease = ""

# 출력 디렉토리
$outputDirectory = "$projectRoot/bin"
# $libOutputDirectory = "$projectRoot/lib"
# $archiveOutDirectory = "$projectRoot/lib"

### FUNCTIONS ##################################################################

function concatOption {
    param(
        [string]$opt,
        [string[]]$argList
    )
    # if($argv) { $ret = "-$opt $argv" } else { $ret = "" }
    $ret = ""
    foreach($a in $argList) {
        if($a -ne "") {
            $ret += "-$opt""$a"" "
        }
    }
    return $ret
}

function getBuildTypeOptions {
    $ret = ""
    if($buildType -eq "Debug") {
        $ret = "$cxxFlagsDebug $exeLinkerFlagsDebug"
    }
    elseif($buildType -eq "Release") {
        $ret = "$cxxFlagsRelease $exeLinkerFlagsRelease"
    }
    return $ret
}

### PRE-PROCESS ################################################################

if($args[0] -eq "Debug") {
    $buildType = "Debug"
}
elseif($args[0] -eq "Release") {
    $buildType = "Release"
}
else {
    Write-Host "build.ps1 [Debug|Release]"
    Exit 0
}

New-Item $outputDirectory -ItemType Directory -ErrorAction SilentlyContinue

### MAIN #######################################################################

$cmd = "$cxxCompiler"
$cmd += " $compileOption".TrimEnd()
$cmd += " $linkOption".TrimEnd()
$cmd += " $(concatOption I $includeDirectories)".TrimEnd()
$cmd += " $(concatOption l $linkLibraries)".TrimEnd()
$cmd += " $(concatOption L $linkDirectories)".TrimEnd()
$cmd += " $(getBuildTypeOptions)".TrimEnd()
$cmd += " $(concatOption o "$outputDirectory/$outputFileName")".TrimEnd()
$cmd += " $srcFiles"

Write-Host $cmd
Invoke-Expression $cmd
