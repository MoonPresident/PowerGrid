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
Date                   :=29/11/2020
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
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./Dependencies/GLFW/include/GLFW $(IncludeSwitch)./Dependencies/GLAD/include $(IncludeSwitch)./Dependencies/stb-master 
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
debug_all:=
Objects0=$(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(ObjectSuffix) $(IntermediateDirectory)/player.cpp$(ObjectSuffix) $(IntermediateDirectory)/DisplayObject.cpp$(ObjectSuffix) $(IntermediateDirectory)/ShaderStore.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/WorldData.cpp$(ObjectSuffix) $(IntermediateDirectory)/shapes.cpp$(ObjectSuffix) $(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix) 



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

$(IntermediateDirectory)/player.cpp$(ObjectSuffix): player.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/player.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/player.cpp$(DependSuffix) -MM player.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkplace/PowerGrid/player.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/player.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/player.cpp$(PreprocessSuffix): player.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/player.cpp$(PreprocessSuffix) player.cpp

$(IntermediateDirectory)/DisplayObject.cpp$(ObjectSuffix): DisplayObject.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DisplayObject.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DisplayObject.cpp$(DependSuffix) -MM DisplayObject.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkplace/PowerGrid/DisplayObject.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DisplayObject.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DisplayObject.cpp$(PreprocessSuffix): DisplayObject.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DisplayObject.cpp$(PreprocessSuffix) DisplayObject.cpp

$(IntermediateDirectory)/ShaderStore.cpp$(ObjectSuffix): ShaderStore.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ShaderStore.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ShaderStore.cpp$(DependSuffix) -MM ShaderStore.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkplace/PowerGrid/ShaderStore.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ShaderStore.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ShaderStore.cpp$(PreprocessSuffix): ShaderStore.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ShaderStore.cpp$(PreprocessSuffix) ShaderStore.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkplace/PowerGrid/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/WorldData.cpp$(ObjectSuffix): WorldData.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/WorldData.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/WorldData.cpp$(DependSuffix) -MM WorldData.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkplace/PowerGrid/WorldData.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/WorldData.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/WorldData.cpp$(PreprocessSuffix): WorldData.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/WorldData.cpp$(PreprocessSuffix) WorldData.cpp

$(IntermediateDirectory)/shapes.cpp$(ObjectSuffix): shapes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shapes.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/shapes.cpp$(DependSuffix) -MM shapes.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkplace/PowerGrid/shapes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/shapes.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shapes.cpp$(PreprocessSuffix): shapes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shapes.cpp$(PreprocessSuffix) shapes.cpp

$(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix): callbacks.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/callbacks.cpp$(DependSuffix) -MM callbacks.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkplace/PowerGrid/callbacks.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/callbacks.cpp$(PreprocessSuffix): callbacks.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/callbacks.cpp$(PreprocessSuffix) callbacks.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


