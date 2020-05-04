##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=optipuzzle
ConfigurationName      :=Release
WorkspacePath          :=/home/peter/CodeLite/OptimizerPuzzle
ProjectPath            :=/home/peter/CodeLite/OptimizerPuzzle/optipuzzle
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Peter
Date                   :=05/04/20
CodeLitePath           :=/home/peter/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="optipuzzle.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_may2020_grid.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_may2020_may.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_may2020_grid.cpp$(ObjectSuffix): src/may2020/grid.cpp $(IntermediateDirectory)/src_may2020_grid.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/peter/CodeLite/OptimizerPuzzle/optipuzzle/src/may2020/grid.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_may2020_grid.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_may2020_grid.cpp$(DependSuffix): src/may2020/grid.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_may2020_grid.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_may2020_grid.cpp$(DependSuffix) -MM src/may2020/grid.cpp

$(IntermediateDirectory)/src_may2020_grid.cpp$(PreprocessSuffix): src/may2020/grid.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_may2020_grid.cpp$(PreprocessSuffix) src/may2020/grid.cpp

$(IntermediateDirectory)/src_may2020_may.cpp$(ObjectSuffix): src/may2020/may.cpp $(IntermediateDirectory)/src_may2020_may.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/peter/CodeLite/OptimizerPuzzle/optipuzzle/src/may2020/may.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_may2020_may.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_may2020_may.cpp$(DependSuffix): src/may2020/may.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_may2020_may.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_may2020_may.cpp$(DependSuffix) -MM src/may2020/may.cpp

$(IntermediateDirectory)/src_may2020_may.cpp$(PreprocessSuffix): src/may2020/may.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_may2020_may.cpp$(PreprocessSuffix) src/may2020/may.cpp

$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix): src/main.cpp $(IntermediateDirectory)/src_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/peter/CodeLite/OptimizerPuzzle/optipuzzle/src/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_main.cpp$(DependSuffix): src/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_main.cpp$(DependSuffix) -MM src/main.cpp

$(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix): src/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_main.cpp$(PreprocessSuffix) src/main.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


