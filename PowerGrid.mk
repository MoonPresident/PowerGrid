##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=PowerGrid
ConfigurationName      :=Debug
WorkspacePath          :=C:/spacelessFolder/CPPWorkspace
ProjectPath            :=C:/spacelessFolder/CPPWorkspace/PowerGrid
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=ThomasSebastian
Date                   :=31/01/2020
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/mingw64/bin/g++.exe
SharedObjectLinkerName :=C:/mingw64/bin/g++.exe -shared -fPIC
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
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="PowerGrid.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/mingw64/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./Dependencies/GLFW/include/GLFW 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)glfw3 $(LibrarySwitch)glfw3 $(LibrarySwitch)glfw3dll $(LibrarySwitch)opengl32 $(LibrarySwitch)gdi32 
ArLibs                 :=  "glfw3.dll" "libglfw3.a" "libglfw3dll.a" "opengl32" "gdi32" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)./Dependencies/GLFW/lib-mingw-w64 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/mingw64/bin/ar.exe rcu
CXX      := C:/mingw64/bin/g++.exe
CC       := C:/mingw64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix) $(IntermediateDirectory)/triangle.cpp$(ObjectSuffix) $(IntermediateDirectory)/player.cpp$(ObjectSuffix) $(IntermediateDirectory)/shapes.cpp$(ObjectSuffix) 



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
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix): callbacks.cpp $(IntermediateDirectory)/callbacks.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/callbacks.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/callbacks.cpp$(DependSuffix): callbacks.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/callbacks.cpp$(DependSuffix) -MM callbacks.cpp

$(IntermediateDirectory)/callbacks.cpp$(PreprocessSuffix): callbacks.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/callbacks.cpp$(PreprocessSuffix) callbacks.cpp

$(IntermediateDirectory)/triangle.cpp$(ObjectSuffix): triangle.cpp $(IntermediateDirectory)/triangle.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/triangle.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/triangle.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/triangle.cpp$(DependSuffix): triangle.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/triangle.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/triangle.cpp$(DependSuffix) -MM triangle.cpp

$(IntermediateDirectory)/triangle.cpp$(PreprocessSuffix): triangle.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/triangle.cpp$(PreprocessSuffix) triangle.cpp

$(IntermediateDirectory)/player.cpp$(ObjectSuffix): player.cpp $(IntermediateDirectory)/player.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/player.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/player.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/player.cpp$(DependSuffix): player.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/player.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/player.cpp$(DependSuffix) -MM player.cpp

$(IntermediateDirectory)/player.cpp$(PreprocessSuffix): player.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/player.cpp$(PreprocessSuffix) player.cpp

$(IntermediateDirectory)/shapes.cpp$(ObjectSuffix): shapes.cpp $(IntermediateDirectory)/shapes.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/shapes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/shapes.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shapes.cpp$(DependSuffix): shapes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shapes.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/shapes.cpp$(DependSuffix) -MM shapes.cpp

$(IntermediateDirectory)/shapes.cpp$(PreprocessSuffix): shapes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shapes.cpp$(PreprocessSuffix) shapes.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


