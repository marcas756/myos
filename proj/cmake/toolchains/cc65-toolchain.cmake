# CMake toolchain file for cc65
# This is largely a result of experimentation, so some things may be done
# suboptimally/wrong. Some compilation options/CMake features may not work.
# Some generators will also not work (like MSVS). Ninja and Makefiles have
# been tested to work.
# What is supported: C, assembly, static libraries

# Setzt das Zielsystem auf 'Generic' für Cross-Compiling,
# was notwendig ist, wenn keine standardmäßige Plattform verwendet wird.
# Dies ermöglicht die Konfiguration mit benutzerdefinierten oder speziellen
# Einstellungen, ohne Annahmen über bekanntes Betriebssystem zu treffen.
set( CMAKE_SYSTEM_NAME Generic )

# Assembler
# -----------------------------------------------------------------------------
set( CMAKE_ASM_SOURCE_FILE_EXTENSIONS s;S;asm )
set( CMAKE_ASM_COMPILER cl65 )
set( CMAKE_ASM_COMPILER_ID cc65 )

# Diese Einstellungen werden verwendet, um Cross-Compiling-Probleme zu überwinden,
# die durch die Nutzung eines speziellen Compilers (cc65) in einer Umgebung entstehen können,
# in der direkte Tests des Compilers nicht möglich sind.
#
# 1. CMAKE_ASM_COMPILER_ID_RUN: Diese Einstellung setzt TRUE, um automatische
#    Kompatibilitäts- und Funktionsprüfungen des Compilers zu überspringen. Dies ist 
#    notwendig in Cross-Compiling-Umgebungen, wo die Tests auf dem Hostsystem nicht
#    anwendbar sind.
#
set( CMAKE_ASM_COMPILER_ID_RUN TRUE )
#
# 2. CMAKE_ASM_COMPILER_ID_WORKS: Durch das Festlegen dieser Variable auf TRUE wird
#    angenommen, dass der Compiler funktionsfähig ist und alle erforderlichen Prüfungen 
#    erfolgreich besteht. Dies verhindert Fehlkonfigurationen durch fehlgeschlagene 
#    Tests.
#
set( CMAKE_ASM_COMPILER_ID_WORKS TRUE )
#
# 3. CMAKE_ASM_COMPILER_ID_FORCED: Diese Einstellung erzwingt die Nutzung einer spezifischen
#    Compiler-ID (in diesem Fall 'cc65'), um sicherzustellen, dass der richtige Compiler
#    verwendet wird und keine Fehlinterpretationen durch automatische Erkennung 
#    auftreten. Dies gewährleistet Konsistenz über verschiedene Projekte oder Konfigurationen.
#
# Zusammen sorgen diese Einstellungen dafür, dass CMake die richtige Compiler-Konfiguration
# annimmt und reibungslos fortsetzt, ohne unzuverlässige Tests durchzuführen.
#
set( CMAKE_ASM_COMPILER_ID_FORCED TRUE )



set( CMAKE_DEPFILE_FLAGS_ASM "--create-dep <DEPFILE>")
set( CMAKE_ASM_VERBOSE_FLAG "-v" )
set( CMAKE_ASM_FLAGS_DEBUG_INIT "-g" )

# C Compiler
# -----------------------------------------------------------------------------
set( CMAKE_C_SOURCE_FILE_EXTENSIONS c )
set( CMAKE_C_COMPILER cl65 )
set( CMAKE_C_COMPILER_ID cc65 )

# Diese Einstellungen werden verwendet, um Cross-Compiling-Probleme zu überwinden,
# die durch die Nutzung eines speziellen Compilers (cc65) in einer Umgebung entstehen können,
# in der direkte Tests des Compilers nicht möglich sind.
#
# 1. CMAKE_ASM_COMPILER_ID_RUN: Diese Einstellung setzt TRUE, um automatische
#    Kompatibilitäts- und Funktionsprüfungen des Compilers zu überspringen. Dies ist 
#    notwendig in Cross-Compiling-Umgebungen, wo die Tests auf dem Hostsystem nicht
#    anwendbar sind.
#
set( CMAKE_C_COMPILER_ID_RUN TRUE )
#
# 2. CMAKE_ASM_COMPILER_ID_WORKS: Durch das Festlegen dieser Variable auf TRUE wird
#    angenommen, dass der Compiler funktionsfähig ist und alle erforderlichen Prüfungen 
#    erfolgreich besteht. Dies verhindert Fehlkonfigurationen durch fehlgeschlagene 
#    Tests.
#
set( CMAKE_C_COMPILER_ID_WORKS TRUE )
#
# 3. CMAKE_ASM_COMPILER_ID_FORCED: Diese Einstellung erzwingt die Nutzung einer spezifischen
#    Compiler-ID (in diesem Fall 'cc65'), um sicherzustellen, dass der richtige Compiler
#    verwendet wird und keine Fehlinterpretationen durch automatische Erkennung 
#    auftreten. Dies gewährleistet Konsistenz über verschiedene Projekte oder Konfigurationen.
#
# Zusammen sorgen diese Einstellungen dafür, dass CMake die richtige Compiler-Konfiguration
# annimmt und reibungslos fortsetzt, ohne unzuverlässige Tests durchzuführen.
#
set( CMAKE_ASM_COMPILER_ID_FORCED TRUE )


set( CMAKE_DEPFILE_FLAGS_C "--create-dep <DEPFILE>")
set( CMAKE_C_VERBOSE_FLAG "-v" )
set( CMAKE_C_FLAGS_DEBUG_INIT "-g" )




# \todo Not sure why CACHE is required here. Seems like something empties
#       this variable after this script has ran...
set( CMAKE_AR "ar65" CACHE PATH "archive" )

# \note Need to delete the old file first because ar65 can only add files
#       into an archive (or remove named files, but we don't know the names).
set( CMAKE_C_CREATE_STATIC_LIBRARY
    "${CMAKE_COMMAND} -E remove <TARGET> "
    "<CMAKE_AR> a <TARGET> <LINK_FLAGS> <OBJECTS>"
)
set( CMAKE_ASM_CREATE_STATIC_LIBRARY ${CMAKE_C_CREATE_STATIC_LIBRARY} )

set(CMAKE_EXE_LINKER_FLAGS "-m .map")
