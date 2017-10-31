#!/bin/bash

RUN_EXE=false

FILES=idl/*.idl
BOILER_FOLDER_FILES=boilerplates/*
MAKE_FOLDER_FILES=makefile/*

for f in $FILES
	
do
	#get the IDL filename for generating the supporting boilertemplates
	IDL_NAME=$(basename $f .idl)
	#echo $IDL_NAME		
	IDL_STRUCT_NAME="$(cat $f | grep 'struct')"
	IDL_STRUCT_NAME="`echo $IDL_STRUCT_NAME | sed 's/struct //g'`"
	echo $IDL_STRUCT_NAME	

	IDL_BUILD_FOLDER=${IDL_NAME}$"_Build"
	#echo $IDL_BUILD_FOLDER 
	
	#create directory for storing the dependency files to make the .exe
	if [ ! -d IDL_BUILD_FOLDER ]; then
		mkdir $IDL_BUILD_FOLDER	
	else
		rm -rf $IDL_BUILD_FOLDER$"/*"
	fi

	#copy boilertemplates to the IDL name
	for b in $BOILER_FOLDER_FILES
	do
		BOILER_FILE=$(basename $b)
		cp $b $IDL_BUILD_FOLDER
	done

	#copy makefile to the generated IDL folder
	for b in $MAKE_FOLDER_FILES
	do
		MAKE_FILE=$(basename $b)
		cp $b $IDL_BUILD_FOLDER
	done	

	cd $IDL_BUILD_FOLDER
	#rename boilertemplates to the IDL name
	rename -f 's/Boiler/'$IDL_NAME'/g' *
	#rename -f 's/\<Boiler\>/'$IDL_NAME'/g' *.h
	
	IDL_NAME_LOWCASE="`echo $IDL_NAME | tr '[:upper:]' '[:lower:]'`"
	rename -f 's/_boiler/'_$IDL_NAME_LOWCASE'/g' *

	for f in *
	do
	#ordering of operation is important to replace boiler string text
	sed -i -e 's/Boiler/'$IDL_NAME'/g' $f
	sed -i -e 's/boiler/'$IDL_NAME_LOWCASE'/g' $f
	sed -i -e 's/BOILER_STRUCT_TYPE_/'$IDL_STRUCT_NAME'/g' $f
	done
	cd ..	

	#generate prismtech idl files
	IDL_FILE=${IDL_NAME}$".idl"
	idlpp -S -l cpp $"idl/"$IDL_FILE -d $IDL_BUILD_FOLDER

	#run CMAKE
	cd $IDL_BUILD_FOLDER
	make -f Makefile
	
	#run the executable if you want
	if [ "$RUN_EXE" == "true" ]; then
		xterm -hold -e ./${IDL_NAME}$"Publisher" &
		xterm -hold -e ./${IDL_NAME}$"Subscriber"
	fi	

	cd ..
	
done
