# - Find ROOT instalation
# This module tries to find the ROOT installation on your system.
# It tries to find the root-config script which gives you all the needed information.
# If the system variable ROOTSYS is set this is straight forward.
# If not the module uses the pathes given in ROOT_CONFIG_SEARCHPATH.
# If you need an other path you should add this path to this varaible.  
# The root-config script is then used to detect basically everything else.
# This module defines a number of key variables and macros.


MESSAGE(STATUS "Looking for Root...")

SET(ROOT_CONFIG_SEARCHPATH
  ${SIMPATH}/tools/root/bin
  ${SIMPATH}/bin
  $ENV{ROOTSYS}/bin
)

SET(ROOT_DEFINITIONS "")

SET(ROOT_INSTALLED_VERSION_TOO_OLD FALSE)

SET(ROOT_CONFIG_EXECUTABLE ROOT_CONFIG_EXECUTABLE-NOTFOUND)

FIND_PROGRAM(ROOT_CONFIG_EXECUTABLE NAMES root-config PATHS
   ${ROOT_CONFIG_SEARCHPATH}
   NO_DEFAULT_PATH)
    
IF (${ROOT_CONFIG_EXECUTABLE} MATCHES "ROOT_CONFIG_EXECUTABLE-NOTFOUND")
  MESSAGE( FATAL_ERROR "ROOT not installed in the searchpath and ROOTSYS is not set. Please
 set ROOTSYS or add the path to your ROOT installation in the Macro FindROOT.cmake in the
 subdirectory cmake/modules.")
ELSE (${ROOT_CONFIG_EXECUTABLE} MATCHES "ROOT_CONFIG_EXECUTABLE-NOTFOUND")
  STRING(REGEX REPLACE "(^.*)/bin/root-config" "\\1" test ${ROOT_CONFIG_EXECUTABLE}) 
  SET( ENV{ROOTSYS} ${test})
  set( ROOTSYS ${test})
ENDIF (${ROOT_CONFIG_EXECUTABLE} MATCHES "ROOT_CONFIG_EXECUTABLE-NOTFOUND")  

 
IF (ROOT_CONFIG_EXECUTABLE)
   
  SET(ROOT_FOUND FALSE)

  EXECUTE_PROCESS(COMMAND ${ROOT_CONFIG_EXECUTABLE} --version OUTPUT_VARIABLE ROOTVERSION)
  EXECUTE_PROCESS( COMMAND ${ROOT_CONFIG_EXECUTABLE} --prefix
    OUTPUT_VARIABLE ROOT_INSTALL_DIR)
  String(STRIP ${ROOTVERSION} ROOTVERSION)
  String(STRIP ${ROOT_INSTALL_DIR} ROOT_INSTALL_DIR)

  MESSAGE(STATUS "Looking for Root... - Found ${ROOT_INSTALL_DIR}/bin/root")
  MESSAGE(STATUS "Looking for Root... - version ${ROOTVERSION} ")   

  # we need at least version 5.00/00
  IF (NOT ROOT_MIN_VERSION)
    SET(ROOT_MIN_VERSION "5.00/00")
  ENDIF (NOT ROOT_MIN_VERSION)
   
  # now parse the parts of the user given version string into variables
  STRING(REGEX REPLACE "^([0-9]+)\\.[0-9][0-9]+\\/[0-9][0-9]+" "\\1" req_root_major_vers "${ROOT_MIN_VERSION}")
  STRING(REGEX REPLACE "^[0-9]+\\.([0-9][0-9])+\\/[0-9][0-9]+.*" "\\1" req_root_minor_vers "${ROOT_MIN_VERSION}")
  STRING(REGEX REPLACE "^[0-9]+\\.[0-9][0-9]+\\/([0-9][0-9]+)" "\\1" req_root_patch_vers "${ROOT_MIN_VERSION}")
   
  # and now the version string given by qmake
  STRING(REGEX REPLACE "^([0-9]+)\\.[0-9][0-9]+\\/[0-9][0-9]+.*" "\\1" found_root_major_vers "${ROOTVERSION}")
  STRING(REGEX REPLACE "^[0-9]+\\.([0-9][0-9])+\\/[0-9][0-9]+.*" "\\1" found_root_minor_vers "${ROOTVERSION}")
  STRING(REGEX REPLACE "^[0-9]+\\.[0-9][0-9]+\\/([0-9][0-9]+).*" "\\1" found_root_patch_vers "${ROOTVERSION}")

  IF (found_root_major_vers LESS 5)
    MESSAGE( FATAL_ERROR "Invalid ROOT version \"${ROOTERSION}\", at least major version 4 is required, e.g. \"5.00/00\"")
  ENDIF (found_root_major_vers LESS 5)

  # compute an overall version number which can be compared at once
  MATH(EXPR req_vers "${req_root_major_vers}*10000 + ${req_root_minor_vers}*100 + ${req_root_patch_vers}")
  MATH(EXPR found_vers "${found_root_major_vers}*10000 + ${found_root_minor_vers}*100 + ${found_root_patch_vers}")
   
  IF (found_vers LESS req_vers)
    SET(ROOT_FOUND FALSE)
    SET(ROOT_INSTALLED_VERSION_TOO_OLD TRUE)
  ELSE (found_vers LESS req_vers)
    SET(ROOT_FOUND TRUE)
  ENDIF (found_vers LESS req_vers)

ENDIF (ROOT_CONFIG_EXECUTABLE)


IF (ROOT_FOUND)

  # ask root-config for the library dir
  # Set ROOT_LIBRARY_DIR

  EXEC_PROGRAM( ${ROOT_CONFIG_EXECUTABLE}
    ARGS "--libdir"
    OUTPUT_VARIABLE ROOT_LIBRARY_DIR_TMP )

  IF(EXISTS "${ROOT_LIBRARY_DIR_TMP}")
    SET(ROOT_LIBRARY_DIR ${ROOT_LIBRARY_DIR_TMP} )
  ELSE(EXISTS "${ROOT_LIBRARY_DIR_TMP}")
    MESSAGE("Warning: ROOT_CONFIG_EXECUTABLE reported ${ROOT_LIBRARY_DIR_TMP} as library path,")
    MESSAGE("Warning: but ${ROOT_LIBRARY_DIR_TMP} does NOT exist, ROOT must NOT be installed correctly.")
  ENDIF(EXISTS "${ROOT_LIBRARY_DIR_TMP}")
    
  # ask root-config for the binary dir
  EXEC_PROGRAM(${ROOT_CONFIG_EXECUTABLE}
    ARGS "--bindir"
    OUTPUT_VARIABLE root_bins )
  SET(ROOT_BINARY_DIR ${root_bins})

  # ask root-config for the include dir
  EXEC_PROGRAM( ${ROOT_CONFIG_EXECUTABLE}
    ARGS "--incdir" 
    OUTPUT_VARIABLE root_headers )
  SET(ROOT_INCLUDE_DIR ${root_headers})
      # CACHE INTERNAL "")

  # ask root-config for the library varaibles
  EXEC_PROGRAM( ${ROOT_CONFIG_EXECUTABLE}
#    ARGS "--noldflags --noauxlibs --libs" 
    ARGS "--glibs" 
    OUTPUT_VARIABLE root_flags )

#  STRING(REGEX MATCHALL "([^ ])+"  root_libs_all ${root_flags})
#  STRING(REGEX MATCHALL "-L([^ ])+"  root_library ${root_flags})
#  REMOVE_FROM_LIST(root_flags "${root_libs_all}" "${root_library}")

  SET(ROOT_LIBRARIES ${root_flags})

  # Make variables changeble to the advanced user
  MARK_AS_ADVANCED( ROOT_LIBRARY_DIR ROOT_INCLUDE_DIR ROOT_DEFINITIONS)

  # Set ROOT_INCLUDES
  SET( ROOT_INCLUDES ${ROOT_INCLUDE_DIR})

  SET(LD_LIBRARY_PATH ${LD_LIBRARY_PATH} ${ROOT_LIBRARY_DIR})

  #######################################
  #
  #       Check the executables of ROOT 
  #          ( rootcint ) 
  #
  #######################################

  FIND_PROGRAM(ROOT_CINT_EXECUTABLE
    NAMES rootcint
    PATHS ${ROOT_BINARY_DIR}
    NO_DEFAULT_PATH
    )

ENDIF (ROOT_FOUND)



function(Format _output input prefix suffix)

# DevNotes - input should be put in quotes or the complete list does not get passed to the function
  set(format)
  foreach(arg ${input})
    set(item ${arg})
    if(prefix)
      string(REGEX MATCH "^${prefix}" pre ${arg})
    endif(prefix)
    if(suffix)
      string(REGEX MATCH "${suffix}$" suf ${arg})
    endif(suffix)
    if(NOT pre)
      set(item "${prefix}${item}")
    endif(NOT pre)
    if(NOT suf)
      set(item "${item}${suffix}")
    endif(NOT suf)
    list(APPEND format ${item})
  endforeach(arg)
  set(${_output} ${format} PARENT_SCOPE)

endfunction(Format)


  ###########################################
  #
  #       Macros for building ROOT dictionary
  #
  ###########################################
Macro(ROOT_GENERATE_DICTIONARY)

  # Macro to switch between the old implementation with parameters
  # and the new implementation without parameters.
  # For the new implementation some CMake variables has to be defined
  # before calling the macro.

  If(${ARGC} EQUAL 0)
#    Message("New Version")
    ROOT_GENERATE_DICTIONARY_NEW()
  Else(${ARGC} EQUAL 0)
    If(${ARGC} EQUAL 4)
#      Message("Old Version")
      ROOT_GENERATE_DICTIONARY_OLD("${ARGV0}" "${ARGV1}" "${ARGV2}" "${ARGV3}")
    Else(${ARGC} EQUAL 4)
      Message(FATAL_ERROR "Has to be implemented")  
    EndIf(${ARGC} EQUAL 4)
  EndIf(${ARGC} EQUAL 0)
 
EndMacro(ROOT_GENERATE_DICTIONARY)

Macro(ROOT_GENERATE_DICTIONARY_NEW)

  # All Arguments needed for this new version of the macro are defined
  # in the parent scope, namely in the CMakeLists.txt of the submodule 
  set(Int_LINKDEF ${LINKDEF})
  set(Int_DICTIONARY ${DICTIONARY})

  Message("DEFINITIONS: ${DEFINITIONS}")
  set(Int_INC ${INCLUDE_DIRECTORIES})
  set(Int_HDRS ${HDRS})
  set(Int_DEF ${DEFINITIONS})

  # Convert the values of the variable to a semi-colon separated list
  separate_arguments(Int_INC)
  separate_arguments(Int_HDRS)
  separate_arguments(Int_DEF)

  # Format neccesary arguments
  # Add -I and -D to include directories and definitions
  Format(Int_INC "${Int_INC}" "-I" "")
  Format(Int_DEF "${Int_DEF}" "-D" "")

  set_source_files_properties(${Int_DICTIONARY} PROPERTIES GENERATED TRUE)
  If (CMAKE_SYSTEM_NAME MATCHES Linux)
    add_custom_command(OUTPUT  ${Int_DICTIONARY}
                       COMMAND LD_LIBRARY_PATH=${ROOT_LIBRARY_DIR}:${_intel_lib_dirs} ROOTSYS=${ROOTSYS} ${ROOT_CINT_EXECUTABLE} -f ${Int_DICTIONARY} -c -p ${Int_DEF} ${Int_INC} ${Int_HDRS} ${Int_LINKDEF}
                       DEPENDS ${Int_HDRS} ${Int_LINKDEF}
                       )
  Else (CMAKE_SYSTEM_NAME MATCHES Linux)
    If (CMAKE_SYSTEM_NAME MATCHES Darwin)
      add_custom_command(OUTPUT  ${Int_DICTIONARY}
                         COMMAND DYLD_LIBRARY_PATH=${ROOT_LIBRARY_DIR} ROOTSYS=${ROOTSYS} ${ROOT_CINT_EXECUTABLE} -f ${Int_DICTIONARY} -c -p  ${Int_DEF} ${Int_INC} ${Int_HDRS} ${Int_LINKDEF}
                         DEPENDS ${Int_HDRS} ${Int_LINKDEF}
                         )
    EndIf (CMAKE_SYSTEM_NAME MATCHES Darwin)
  EndIf (CMAKE_SYSTEM_NAME MATCHES Linux)


endmacro(ROOT_GENERATE_DICTIONARY_NEW)


MACRO (ROOT_GENERATE_DICTIONARY_OLD INFILES LINKDEF_FILE OUTFILE INCLUDE_DIRS_IN)
 
  set(INCLUDE_DIRS)

  foreach (_current_FILE ${INCLUDE_DIRS_IN})
    set(INCLUDE_DIRS ${INCLUDE_DIRS} -I${_current_FILE})   
  endforeach (_current_FILE ${INCLUDE_DIRS_IN})
 
#  Message("Definitions: ${DEFINITIONS}")
#  MESSAGE("INFILES: ${INFILES}")
#  MESSAGE("OutFILE: ${OUTFILE}")
#  MESSAGE("LINKDEF_FILE: ${LINKDEF_FILE}")
#  MESSAGE("INCLUDE_DIRS: ${INCLUDE_DIRS}")

  STRING(REGEX REPLACE "^(.*)\\.(.*)$" "\\1.h" bla "${OUTFILE}")
#  MESSAGE("BLA: ${bla}")
  SET (OUTFILES ${OUTFILE} ${bla})


  if (CMAKE_SYSTEM_NAME MATCHES Linux)
    ADD_CUSTOM_COMMAND(OUTPUT ${OUTFILES}
       COMMAND LD_LIBRARY_PATH=${ROOT_LIBRARY_DIR}:${_intel_lib_dirs} ROOTSYS=${ROOTSYS} ${ROOT_CINT_EXECUTABLE}
       ARGS -f ${OUTFILE} -c -p -DHAVE_CONFIG_H ${INCLUDE_DIRS} ${INFILES} ${LINKDEF_FILE} DEPENDS ${INFILES} ${LINKDEF_FILE})
  else (CMAKE_SYSTEM_NAME MATCHES Linux)
    if (CMAKE_SYSTEM_NAME MATCHES Darwin)
      ADD_CUSTOM_COMMAND(OUTPUT ${OUTFILES}
       COMMAND DYLD_LIBRARY_PATH=${ROOT_LIBRARY_DIR} ROOTSYS=${ROOTSYS} ${ROOT_CINT_EXECUTABLE}
       ARGS -f ${OUTFILE} -c -p -DHAVE_CONFIG_H ${INCLUDE_DIRS} ${INFILES} ${LINKDEF_FILE} DEPENDS ${INFILES} ${LINKDEF_FILE})
    endif (CMAKE_SYSTEM_NAME MATCHES Darwin)
  endif (CMAKE_SYSTEM_NAME MATCHES Linux)

ENDMACRO (ROOT_GENERATE_DICTIONARY_OLD)

MACRO (GENERATE_ROOT_TEST_SCRIPT SCRIPT_FULL_NAME)

  get_filename_component(path_name ${SCRIPT_FULL_NAME} PATH)
  get_filename_component(file_extension ${SCRIPT_FULL_NAME} EXT)
  get_filename_component(file_name ${SCRIPT_FULL_NAME} NAME_WE)
  set(shell_script_name "${file_name}.sh")

  #MESSAGE("PATH: ${path_name}")
  #MESSAGE("Ext: ${file_extension}")
  #MESSAGE("Name: ${file_name}")
  #MESSAGE("Shell Name: ${shell_script_name}")

  string(REPLACE ${PROJECT_SOURCE_DIR} 
         ${PROJECT_BINARY_DIR} new_path ${path_name}
        )

  #MESSAGE("New PATH: ${new_path}")

  file(MAKE_DIRECTORY ${new_path}/data)

  CONVERT_LIST_TO_STRING(${LD_LIBRARY_PATH})
  set(MY_LD_LIBRARY_PATH ${output})
  set(my_script_name ${SCRIPT_FULL_NAME})

  if(CMAKE_SYSTEM MATCHES Darwin)
    configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/root_macro_macos.sh.in
                   ${new_path}/${shell_script_name}
                  )
  else(CMAKE_SYSTEM MATCHES Darwin)
    configure_file(${PROJECT_SOURCE_DIR}/cmake/scripts/root_macro.sh.in
                   ${new_path}/${shell_script_name}
                  )
  endif(CMAKE_SYSTEM MATCHES Darwin)

  EXEC_PROGRAM(/bin/chmod ARGS "u+x  ${new_path}/${shell_script_name}")

ENDMACRO (GENERATE_ROOT_TEST_SCRIPT)