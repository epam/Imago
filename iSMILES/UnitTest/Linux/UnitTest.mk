##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=UnitTest
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/sic/iSMILES/UnitTest/Linux"
ProjectPath            := "/home/sic/iSMILES/UnitTest/Linux"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=sic
Date                   :=18.11.2010
CodeLitePath           :="/home/sic/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)png 
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/UnitTest_main$(ObjectSuffix) $(IntermediateDirectory)/UnitTest_Draw$(ObjectSuffix) $(IntermediateDirectory)/Image_FilePNG$(ObjectSuffix) $(IntermediateDirectory)/Image_ImageFilter$(ObjectSuffix) $(IntermediateDirectory)/Image_Image$(ObjectSuffix) $(IntermediateDirectory)/Vectorization_ImageMap$(ObjectSuffix) $(IntermediateDirectory)/Vectorization_Bounds$(ObjectSuffix) $(IntermediateDirectory)/Vectorization_LinearApproximation$(ObjectSuffix) $(IntermediateDirectory)/Vectorization_RangeArray$(ObjectSuffix) $(IntermediateDirectory)/Vectorization_Contour$(ObjectSuffix) \
	$(IntermediateDirectory)/Vectorization_Vectorize$(ObjectSuffix) $(IntermediateDirectory)/Vectorization_TriangleRecognize$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/UnitTest_main$(ObjectSuffix): ../main.cpp $(IntermediateDirectory)/UnitTest_main$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sic/iSMILES/UnitTest/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/UnitTest_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UnitTest_main$(DependSuffix): ../main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/UnitTest_main$(ObjectSuffix) -MF$(IntermediateDirectory)/UnitTest_main$(DependSuffix) -MM "/home/sic/iSMILES/UnitTest/main.cpp"

$(IntermediateDirectory)/UnitTest_main$(PreprocessSuffix): ../main.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UnitTest_main$(PreprocessSuffix) "/home/sic/iSMILES/UnitTest/main.cpp"

$(IntermediateDirectory)/UnitTest_Draw$(ObjectSuffix): ../Draw.cpp $(IntermediateDirectory)/UnitTest_Draw$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sic/iSMILES/UnitTest/Draw.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/UnitTest_Draw$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UnitTest_Draw$(DependSuffix): ../Draw.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/UnitTest_Draw$(ObjectSuffix) -MF$(IntermediateDirectory)/UnitTest_Draw$(DependSuffix) -MM "/home/sic/iSMILES/UnitTest/Draw.cpp"

$(IntermediateDirectory)/UnitTest_Draw$(PreprocessSuffix): ../Draw.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UnitTest_Draw$(PreprocessSuffix) "/home/sic/iSMILES/UnitTest/Draw.cpp"

$(IntermediateDirectory)/Image_FilePNG$(ObjectSuffix): ../../src/Image/FilePNG.cpp $(IntermediateDirectory)/Image_FilePNG$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sic/iSMILES/src/Image/FilePNG.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Image_FilePNG$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Image_FilePNG$(DependSuffix): ../../src/Image/FilePNG.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Image_FilePNG$(ObjectSuffix) -MF$(IntermediateDirectory)/Image_FilePNG$(DependSuffix) -MM "/home/sic/iSMILES/src/Image/FilePNG.cpp"

$(IntermediateDirectory)/Image_FilePNG$(PreprocessSuffix): ../../src/Image/FilePNG.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Image_FilePNG$(PreprocessSuffix) "/home/sic/iSMILES/src/Image/FilePNG.cpp"

$(IntermediateDirectory)/Image_ImageFilter$(ObjectSuffix): ../../src/Image/ImageFilter.cpp $(IntermediateDirectory)/Image_ImageFilter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sic/iSMILES/src/Image/ImageFilter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Image_ImageFilter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Image_ImageFilter$(DependSuffix): ../../src/Image/ImageFilter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Image_ImageFilter$(ObjectSuffix) -MF$(IntermediateDirectory)/Image_ImageFilter$(DependSuffix) -MM "/home/sic/iSMILES/src/Image/ImageFilter.cpp"

$(IntermediateDirectory)/Image_ImageFilter$(PreprocessSuffix): ../../src/Image/ImageFilter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Image_ImageFilter$(PreprocessSuffix) "/home/sic/iSMILES/src/Image/ImageFilter.cpp"

$(IntermediateDirectory)/Image_Image$(ObjectSuffix): ../../src/Image/Image.cpp $(IntermediateDirectory)/Image_Image$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sic/iSMILES/src/Image/Image.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Image_Image$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Image_Image$(DependSuffix): ../../src/Image/Image.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Image_Image$(ObjectSuffix) -MF$(IntermediateDirectory)/Image_Image$(DependSuffix) -MM "/home/sic/iSMILES/src/Image/Image.cpp"

$(IntermediateDirectory)/Image_Image$(PreprocessSuffix): ../../src/Image/Image.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Image_Image$(PreprocessSuffix) "/home/sic/iSMILES/src/Image/Image.cpp"

$(IntermediateDirectory)/Vectorization_ImageMap$(ObjectSuffix): ../../src/Vectorization/ImageMap.cpp $(IntermediateDirectory)/Vectorization_ImageMap$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sic/iSMILES/src/Vectorization/ImageMap.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Vectorization_ImageMap$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Vectorization_ImageMap$(DependSuffix): ../../src/Vectorization/ImageMap.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Vectorization_ImageMap$(ObjectSuffix) -MF$(IntermediateDirectory)/Vectorization_ImageMap$(DependSuffix) -MM "/home/sic/iSMILES/src/Vectorization/ImageMap.cpp"

$(IntermediateDirectory)/Vectorization_ImageMap$(PreprocessSuffix): ../../src/Vectorization/ImageMap.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Vectorization_ImageMap$(PreprocessSuffix) "/home/sic/iSMILES/src/Vectorization/ImageMap.cpp"

$(IntermediateDirectory)/Vectorization_Bounds$(ObjectSuffix): ../../src/Vectorization/Bounds.cpp $(IntermediateDirectory)/Vectorization_Bounds$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sic/iSMILES/src/Vectorization/Bounds.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Vectorization_Bounds$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Vectorization_Bounds$(DependSuffix): ../../src/Vectorization/Bounds.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Vectorization_Bounds$(ObjectSuffix) -MF$(IntermediateDirectory)/Vectorization_Bounds$(DependSuffix) -MM "/home/sic/iSMILES/src/Vectorization/Bounds.cpp"

$(IntermediateDirectory)/Vectorization_Bounds$(PreprocessSuffix): ../../src/Vectorization/Bounds.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Vectorization_Bounds$(PreprocessSuffix) "/home/sic/iSMILES/src/Vectorization/Bounds.cpp"

$(IntermediateDirectory)/Vectorization_LinearApproximation$(ObjectSuffix): ../../src/Vectorization/LinearApproximation.cpp $(IntermediateDirectory)/Vectorization_LinearApproximation$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sic/iSMILES/src/Vectorization/LinearApproximation.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Vectorization_LinearApproximation$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Vectorization_LinearApproximation$(DependSuffix): ../../src/Vectorization/LinearApproximation.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Vectorization_LinearApproximation$(ObjectSuffix) -MF$(IntermediateDirectory)/Vectorization_LinearApproximation$(DependSuffix) -MM "/home/sic/iSMILES/src/Vectorization/LinearApproximation.cpp"

$(IntermediateDirectory)/Vectorization_LinearApproximation$(PreprocessSuffix): ../../src/Vectorization/LinearApproximation.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Vectorization_LinearApproximation$(PreprocessSuffix) "/home/sic/iSMILES/src/Vectorization/LinearApproximation.cpp"

$(IntermediateDirectory)/Vectorization_RangeArray$(ObjectSuffix): ../../src/Vectorization/RangeArray.cpp $(IntermediateDirectory)/Vectorization_RangeArray$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sic/iSMILES/src/Vectorization/RangeArray.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Vectorization_RangeArray$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Vectorization_RangeArray$(DependSuffix): ../../src/Vectorization/RangeArray.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Vectorization_RangeArray$(ObjectSuffix) -MF$(IntermediateDirectory)/Vectorization_RangeArray$(DependSuffix) -MM "/home/sic/iSMILES/src/Vectorization/RangeArray.cpp"

$(IntermediateDirectory)/Vectorization_RangeArray$(PreprocessSuffix): ../../src/Vectorization/RangeArray.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Vectorization_RangeArray$(PreprocessSuffix) "/home/sic/iSMILES/src/Vectorization/RangeArray.cpp"

$(IntermediateDirectory)/Vectorization_Contour$(ObjectSuffix): ../../src/Vectorization/Contour.cpp $(IntermediateDirectory)/Vectorization_Contour$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sic/iSMILES/src/Vectorization/Contour.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Vectorization_Contour$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Vectorization_Contour$(DependSuffix): ../../src/Vectorization/Contour.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Vectorization_Contour$(ObjectSuffix) -MF$(IntermediateDirectory)/Vectorization_Contour$(DependSuffix) -MM "/home/sic/iSMILES/src/Vectorization/Contour.cpp"

$(IntermediateDirectory)/Vectorization_Contour$(PreprocessSuffix): ../../src/Vectorization/Contour.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Vectorization_Contour$(PreprocessSuffix) "/home/sic/iSMILES/src/Vectorization/Contour.cpp"

$(IntermediateDirectory)/Vectorization_Vectorize$(ObjectSuffix): ../../src/Vectorization/Vectorize.cpp $(IntermediateDirectory)/Vectorization_Vectorize$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sic/iSMILES/src/Vectorization/Vectorize.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Vectorization_Vectorize$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Vectorization_Vectorize$(DependSuffix): ../../src/Vectorization/Vectorize.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Vectorization_Vectorize$(ObjectSuffix) -MF$(IntermediateDirectory)/Vectorization_Vectorize$(DependSuffix) -MM "/home/sic/iSMILES/src/Vectorization/Vectorize.cpp"

$(IntermediateDirectory)/Vectorization_Vectorize$(PreprocessSuffix): ../../src/Vectorization/Vectorize.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Vectorization_Vectorize$(PreprocessSuffix) "/home/sic/iSMILES/src/Vectorization/Vectorize.cpp"

$(IntermediateDirectory)/Vectorization_TriangleRecognize$(ObjectSuffix): ../../src/Vectorization/TriangleRecognize.cpp $(IntermediateDirectory)/Vectorization_TriangleRecognize$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/sic/iSMILES/src/Vectorization/TriangleRecognize.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Vectorization_TriangleRecognize$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Vectorization_TriangleRecognize$(DependSuffix): ../../src/Vectorization/TriangleRecognize.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Vectorization_TriangleRecognize$(ObjectSuffix) -MF$(IntermediateDirectory)/Vectorization_TriangleRecognize$(DependSuffix) -MM "/home/sic/iSMILES/src/Vectorization/TriangleRecognize.cpp"

$(IntermediateDirectory)/Vectorization_TriangleRecognize$(PreprocessSuffix): ../../src/Vectorization/TriangleRecognize.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Vectorization_TriangleRecognize$(PreprocessSuffix) "/home/sic/iSMILES/src/Vectorization/TriangleRecognize.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/UnitTest_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/UnitTest_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/UnitTest_main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/UnitTest_Draw$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/UnitTest_Draw$(DependSuffix)
	$(RM) $(IntermediateDirectory)/UnitTest_Draw$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Image_FilePNG$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Image_FilePNG$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Image_FilePNG$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Image_ImageFilter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Image_ImageFilter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Image_ImageFilter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Image_Image$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Image_Image$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Image_Image$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_ImageMap$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_ImageMap$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_ImageMap$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_Bounds$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_Bounds$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_Bounds$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_LinearApproximation$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_LinearApproximation$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_LinearApproximation$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_RangeArray$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_RangeArray$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_RangeArray$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_Contour$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_Contour$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_Contour$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_Vectorize$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_Vectorize$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_Vectorize$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_TriangleRecognize$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_TriangleRecognize$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Vectorization_TriangleRecognize$(PreprocessSuffix)
	$(RM) $(OutputFile)


