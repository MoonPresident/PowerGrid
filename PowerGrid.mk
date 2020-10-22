##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=PowerGrid
ConfigurationName      :=Debug
WorkspacePath          :=C:/spacelessFolder/CPPWorkplace
ProjectPath            :=C:/spacelessFolder/CPPWorkplace/PowerGrid
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Thomas
Date                   :=22/10/2020
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
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./Dependencies/GLFW/include/GLFW $(IncludeSwitch)./Dependencies/GLAD/include 
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
Objects0=$(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(ObjectSuffix) $(IntermediateDirectory)/shapes.cpp$(ObjectSuffix) $(IntermediateDirectory)/shaderStore.cpp$(ObjectSuffix) $(IntermediateDirectory)/player.cpp$(ObjectSuffix) $(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(ObjectSuffix): Dependencies/GLAD/src/glad.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(DependSuffix) -MM Dependencies/GLAD/src/glad.c
	$(CC) $(SourceSwitch) "C:/spacelessFolder/CPPWorkplace/PowerGrid/Dependencies/GLAD/src/glad.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(PreprocessSuffix): Dependencies/GLAD/src/glad.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(PreprocessSuffix) Dependencies/GLAD/src/glad.c

$(IntermediateDirectory)/shapes.cpp$(ObjectSuffix): shapes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shapes.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/shapes.cpp$(DependSuffix) -MM shapes.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkplace/PowerGrid/shapes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/shapes.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shapes.cpp$(PreprocessSuffix): shapes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shapes.cpp$(PreprocessSuffix) shapes.cpp

$(IntermediateDirectory)/shaderStore.cpp$(ObjectSuffix): shaderStore.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shaderStore.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/shaderStore.cpp$(DependSuffix) -MM shaderStore.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkplace/PowerGrid/shaderStore.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/shaderStore.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shaderStore.cpp$(PreprocessSuffix): shaderStore.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shaderStore.cpp$(PreprocessSuffix) shaderStore.cpp

$(IntermediateDirectory)/player.cpp$(ObjectSuffix): player.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/player.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/player.cpp$(DependSuffix) -MM player.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkplace/PowerGrid/player.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/player.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/player.cpp$(PreprocessSuffix): player.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/player.cpp$(PreprocessSuffix) player.cpp

$(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix): callbacks.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/callbacks.cpp$(DependSuffix) -MM callbacks.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkplace/PowerGrid/callbacks.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/callbacks.cpp$(PreprocessSuffix): callbacks.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/callbacks.cpp$(PreprocessSuffix) callbacks.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkplace/PowerGrid/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


