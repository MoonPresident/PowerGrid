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
Date                   :=31/07/2021
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
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./Dependencies/GLFW/include/GLFW $(IncludeSwitch)./Dependencies/GLAD/include $(IncludeSwitch)./Dependencies/stb-master $(IncludeSwitch)./Dependencies/glm-stable/glm $(IncludeSwitch)./Dependencies/FreeType/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)glfw3 $(LibrarySwitch)glfw3 $(LibrarySwitch)glfw3dll $(LibrarySwitch)opengl32 $(LibrarySwitch)gdi32 $(LibrarySwitch)freetype $(LibrarySwitch)freetype 
ArLibs                 :=  "glfw3.dll" "libglfw3.a" "libglfw3dll.a" "opengl32" "gdi32" "freetype.dll" "freetype" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)./Dependencies/GLFW/lib-mingw-w64 $(LibraryPathSwitch)./Dependencies/glm-stable/ $(LibraryPathSwitch)./Dependencies/FreeType 

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
Objects0=$(IntermediateDirectory)/games_example_game_3D.cpp$(ObjectSuffix) $(IntermediateDirectory)/ShaderStore.cpp$(ObjectSuffix) $(IntermediateDirectory)/WorldData.cpp$(ObjectSuffix) $(IntermediateDirectory)/shapes.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Terminal.cpp$(ObjectSuffix) $(IntermediateDirectory)/DisplayObject.cpp$(ObjectSuffix) $(IntermediateDirectory)/resources_Shape.cpp$(ObjectSuffix) $(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix) $(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(ObjectSuffix) \
	$(IntermediateDirectory)/games_squares_original.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/games_example_game_3D.cpp$(ObjectSuffix): games/example_game_3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/games_example_game_3D.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/games_example_game_3D.cpp$(DependSuffix) -MM games/example_game_3D.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/games/example_game_3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/games_example_game_3D.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/games_example_game_3D.cpp$(PreprocessSuffix): games/example_game_3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/games_example_game_3D.cpp$(PreprocessSuffix) games/example_game_3D.cpp

$(IntermediateDirectory)/ShaderStore.cpp$(ObjectSuffix): ShaderStore.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ShaderStore.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ShaderStore.cpp$(DependSuffix) -MM ShaderStore.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/ShaderStore.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ShaderStore.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ShaderStore.cpp$(PreprocessSuffix): ShaderStore.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ShaderStore.cpp$(PreprocessSuffix) ShaderStore.cpp

$(IntermediateDirectory)/WorldData.cpp$(ObjectSuffix): WorldData.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/WorldData.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/WorldData.cpp$(DependSuffix) -MM WorldData.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/WorldData.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/WorldData.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/WorldData.cpp$(PreprocessSuffix): WorldData.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/WorldData.cpp$(PreprocessSuffix) WorldData.cpp

$(IntermediateDirectory)/shapes.cpp$(ObjectSuffix): shapes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/shapes.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/shapes.cpp$(DependSuffix) -MM shapes.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/shapes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/shapes.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/shapes.cpp$(PreprocessSuffix): shapes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/shapes.cpp$(PreprocessSuffix) shapes.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/Terminal.cpp$(ObjectSuffix): Terminal.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Terminal.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Terminal.cpp$(DependSuffix) -MM Terminal.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/Terminal.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Terminal.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Terminal.cpp$(PreprocessSuffix): Terminal.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Terminal.cpp$(PreprocessSuffix) Terminal.cpp

$(IntermediateDirectory)/DisplayObject.cpp$(ObjectSuffix): DisplayObject.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DisplayObject.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DisplayObject.cpp$(DependSuffix) -MM DisplayObject.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/DisplayObject.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DisplayObject.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DisplayObject.cpp$(PreprocessSuffix): DisplayObject.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DisplayObject.cpp$(PreprocessSuffix) DisplayObject.cpp

$(IntermediateDirectory)/resources_Shape.cpp$(ObjectSuffix): resources/Shape.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/resources_Shape.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/resources_Shape.cpp$(DependSuffix) -MM resources/Shape.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/resources/Shape.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/resources_Shape.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/resources_Shape.cpp$(PreprocessSuffix): resources/Shape.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/resources_Shape.cpp$(PreprocessSuffix) resources/Shape.cpp

$(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix): callbacks.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/callbacks.cpp$(DependSuffix) -MM callbacks.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/callbacks.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/callbacks.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/callbacks.cpp$(PreprocessSuffix): callbacks.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/callbacks.cpp$(PreprocessSuffix) callbacks.cpp

$(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(ObjectSuffix): Dependencies/GLAD/src/glad.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(DependSuffix) -MM Dependencies/GLAD/src/glad.c
	$(CC) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/Dependencies/GLAD/src/glad.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(PreprocessSuffix): Dependencies/GLAD/src/glad.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Dependencies_GLAD_src_glad.c$(PreprocessSuffix) Dependencies/GLAD/src/glad.c

$(IntermediateDirectory)/games_squares_original.cpp$(ObjectSuffix): games/squares_original.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/games_squares_original.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/games_squares_original.cpp$(DependSuffix) -MM games/squares_original.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/spacelessFolder/CPPWorkspace/PowerGrid/games/squares_original.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/games_squares_original.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/games_squares_original.cpp$(PreprocessSuffix): games/squares_original.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/games_squares_original.cpp$(PreprocessSuffix) games/squares_original.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


