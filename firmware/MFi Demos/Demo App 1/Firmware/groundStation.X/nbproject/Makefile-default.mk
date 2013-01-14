#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/groundStation.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/groundStation.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/246327853/I2CAcknowledgeByte.o ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeHasCompleted.o ${OBJECTDIR}/_ext/246327853/I2CBusIsIdle.o ${OBJECTDIR}/_ext/246327853/I2CByteWasAcknowledged.o ${OBJECTDIR}/_ext/246327853/I2CClearStatus.o ${OBJECTDIR}/_ext/246327853/I2CConfigure.o ${OBJECTDIR}/_ext/246327853/I2CEnable.o ${OBJECTDIR}/_ext/246327853/I2CGetByte.o ${OBJECTDIR}/_ext/246327853/I2CGetStatus.o ${OBJECTDIR}/_ext/246327853/I2CPrivate.o ${OBJECTDIR}/_ext/246327853/I2CReceivedByteIsAnAddress.o ${OBJECTDIR}/_ext/246327853/I2CReceivedDataIsAvailable.o ${OBJECTDIR}/_ext/246327853/I2CReceiverEnable.o ${OBJECTDIR}/_ext/246327853/I2CRepeatStart.o ${OBJECTDIR}/_ext/246327853/I2CSendByte.o ${OBJECTDIR}/_ext/246327853/I2CSetFrequencyWithConstant.o ${OBJECTDIR}/_ext/246327853/I2CStart.o ${OBJECTDIR}/_ext/246327853/I2CStop.o ${OBJECTDIR}/_ext/246327853/I2CTransmissionHasCompleted.o ${OBJECTDIR}/_ext/246327853/I2CTransmitterIsReady.o ${OBJECTDIR}/_ext/926214927/MFI_Data.o ${OBJECTDIR}/_ext/926214927/MFI_iPod_UART.o ${OBJECTDIR}/_ext/761559875/mfi_handlers.o ${OBJECTDIR}/_ext/2048740170/DebugUARTBuffered.o ${OBJECTDIR}/_ext/2137914366/LM49450.o ${OBJECTDIR}/_ext/2137914366/MCP9800.o ${OBJECTDIR}/_ext/1472/Tick.o ${OBJECTDIR}/_ext/2048740170/TimeDelay.o ${OBJECTDIR}/_ext/1472/iPxx.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/2137914366/system.o ${OBJECTDIR}/debugQueue.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/246327853/I2CAcknowledgeByte.o.d ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeHasCompleted.o.d ${OBJECTDIR}/_ext/246327853/I2CBusIsIdle.o.d ${OBJECTDIR}/_ext/246327853/I2CByteWasAcknowledged.o.d ${OBJECTDIR}/_ext/246327853/I2CClearStatus.o.d ${OBJECTDIR}/_ext/246327853/I2CConfigure.o.d ${OBJECTDIR}/_ext/246327853/I2CEnable.o.d ${OBJECTDIR}/_ext/246327853/I2CGetByte.o.d ${OBJECTDIR}/_ext/246327853/I2CGetStatus.o.d ${OBJECTDIR}/_ext/246327853/I2CPrivate.o.d ${OBJECTDIR}/_ext/246327853/I2CReceivedByteIsAnAddress.o.d ${OBJECTDIR}/_ext/246327853/I2CReceivedDataIsAvailable.o.d ${OBJECTDIR}/_ext/246327853/I2CReceiverEnable.o.d ${OBJECTDIR}/_ext/246327853/I2CRepeatStart.o.d ${OBJECTDIR}/_ext/246327853/I2CSendByte.o.d ${OBJECTDIR}/_ext/246327853/I2CSetFrequencyWithConstant.o.d ${OBJECTDIR}/_ext/246327853/I2CStart.o.d ${OBJECTDIR}/_ext/246327853/I2CStop.o.d ${OBJECTDIR}/_ext/246327853/I2CTransmissionHasCompleted.o.d ${OBJECTDIR}/_ext/246327853/I2CTransmitterIsReady.o.d ${OBJECTDIR}/_ext/926214927/MFI_Data.o.d ${OBJECTDIR}/_ext/926214927/MFI_iPod_UART.o.d ${OBJECTDIR}/_ext/761559875/mfi_handlers.o.d ${OBJECTDIR}/_ext/2048740170/DebugUARTBuffered.o.d ${OBJECTDIR}/_ext/2137914366/LM49450.o.d ${OBJECTDIR}/_ext/2137914366/MCP9800.o.d ${OBJECTDIR}/_ext/1472/Tick.o.d ${OBJECTDIR}/_ext/2048740170/TimeDelay.o.d ${OBJECTDIR}/_ext/1472/iPxx.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/2137914366/system.o.d ${OBJECTDIR}/debugQueue.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/246327853/I2CAcknowledgeByte.o ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeHasCompleted.o ${OBJECTDIR}/_ext/246327853/I2CBusIsIdle.o ${OBJECTDIR}/_ext/246327853/I2CByteWasAcknowledged.o ${OBJECTDIR}/_ext/246327853/I2CClearStatus.o ${OBJECTDIR}/_ext/246327853/I2CConfigure.o ${OBJECTDIR}/_ext/246327853/I2CEnable.o ${OBJECTDIR}/_ext/246327853/I2CGetByte.o ${OBJECTDIR}/_ext/246327853/I2CGetStatus.o ${OBJECTDIR}/_ext/246327853/I2CPrivate.o ${OBJECTDIR}/_ext/246327853/I2CReceivedByteIsAnAddress.o ${OBJECTDIR}/_ext/246327853/I2CReceivedDataIsAvailable.o ${OBJECTDIR}/_ext/246327853/I2CReceiverEnable.o ${OBJECTDIR}/_ext/246327853/I2CRepeatStart.o ${OBJECTDIR}/_ext/246327853/I2CSendByte.o ${OBJECTDIR}/_ext/246327853/I2CSetFrequencyWithConstant.o ${OBJECTDIR}/_ext/246327853/I2CStart.o ${OBJECTDIR}/_ext/246327853/I2CStop.o ${OBJECTDIR}/_ext/246327853/I2CTransmissionHasCompleted.o ${OBJECTDIR}/_ext/246327853/I2CTransmitterIsReady.o ${OBJECTDIR}/_ext/926214927/MFI_Data.o ${OBJECTDIR}/_ext/926214927/MFI_iPod_UART.o ${OBJECTDIR}/_ext/761559875/mfi_handlers.o ${OBJECTDIR}/_ext/2048740170/DebugUARTBuffered.o ${OBJECTDIR}/_ext/2137914366/LM49450.o ${OBJECTDIR}/_ext/2137914366/MCP9800.o ${OBJECTDIR}/_ext/1472/Tick.o ${OBJECTDIR}/_ext/2048740170/TimeDelay.o ${OBJECTDIR}/_ext/1472/iPxx.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/2137914366/system.o ${OBJECTDIR}/debugQueue.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/groundStation.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F87J11
MP_PROCESSOR_OPTION_LD=18f87j11
MP_LINKER_DEBUG_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/246327853/I2CAcknowledgeByte.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CAcknowledgeByte.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeByte.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeByte.o   "../../../../Microchip/MFI/I2C PIC18/I2CAcknowledgeByte.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeByte.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CAcknowledgeByte.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CAcknowledgeHasCompleted.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CAcknowledgeHasCompleted.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeHasCompleted.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeHasCompleted.o   "../../../../Microchip/MFI/I2C PIC18/I2CAcknowledgeHasCompleted.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeHasCompleted.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CAcknowledgeHasCompleted.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CBusIsIdle.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CBusIsIdle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CBusIsIdle.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CBusIsIdle.o   "../../../../Microchip/MFI/I2C PIC18/I2CBusIsIdle.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CBusIsIdle.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CBusIsIdle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CByteWasAcknowledged.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CByteWasAcknowledged.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CByteWasAcknowledged.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CByteWasAcknowledged.o   "../../../../Microchip/MFI/I2C PIC18/I2CByteWasAcknowledged.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CByteWasAcknowledged.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CByteWasAcknowledged.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CClearStatus.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CClearStatus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CClearStatus.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CClearStatus.o   "../../../../Microchip/MFI/I2C PIC18/I2CClearStatus.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CClearStatus.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CClearStatus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CConfigure.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CConfigure.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CConfigure.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CConfigure.o   "../../../../Microchip/MFI/I2C PIC18/I2CConfigure.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CConfigure.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CConfigure.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CEnable.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CEnable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CEnable.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CEnable.o   "../../../../Microchip/MFI/I2C PIC18/I2CEnable.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CEnable.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CEnable.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CGetByte.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CGetByte.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CGetByte.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CGetByte.o   "../../../../Microchip/MFI/I2C PIC18/I2CGetByte.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CGetByte.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CGetByte.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CGetStatus.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CGetStatus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CGetStatus.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CGetStatus.o   "../../../../Microchip/MFI/I2C PIC18/I2CGetStatus.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CGetStatus.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CGetStatus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CPrivate.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CPrivate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CPrivate.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CPrivate.o   "../../../../Microchip/MFI/I2C PIC18/I2CPrivate.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CPrivate.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CPrivate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CReceivedByteIsAnAddress.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CReceivedByteIsAnAddress.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CReceivedByteIsAnAddress.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CReceivedByteIsAnAddress.o   "../../../../Microchip/MFI/I2C PIC18/I2CReceivedByteIsAnAddress.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CReceivedByteIsAnAddress.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CReceivedByteIsAnAddress.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CReceivedDataIsAvailable.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CReceivedDataIsAvailable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CReceivedDataIsAvailable.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CReceivedDataIsAvailable.o   "../../../../Microchip/MFI/I2C PIC18/I2CReceivedDataIsAvailable.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CReceivedDataIsAvailable.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CReceivedDataIsAvailable.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CReceiverEnable.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CReceiverEnable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CReceiverEnable.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CReceiverEnable.o   "../../../../Microchip/MFI/I2C PIC18/I2CReceiverEnable.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CReceiverEnable.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CReceiverEnable.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CRepeatStart.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CRepeatStart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CRepeatStart.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CRepeatStart.o   "../../../../Microchip/MFI/I2C PIC18/I2CRepeatStart.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CRepeatStart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CRepeatStart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CSendByte.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CSendByte.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CSendByte.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CSendByte.o   "../../../../Microchip/MFI/I2C PIC18/I2CSendByte.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CSendByte.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CSendByte.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CSetFrequencyWithConstant.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CSetFrequencyWithConstant.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CSetFrequencyWithConstant.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CSetFrequencyWithConstant.o   "../../../../Microchip/MFI/I2C PIC18/I2CSetFrequencyWithConstant.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CSetFrequencyWithConstant.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CSetFrequencyWithConstant.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CStart.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CStart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CStart.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CStart.o   "../../../../Microchip/MFI/I2C PIC18/I2CStart.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CStart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CStart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CStop.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CStop.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CStop.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CStop.o   "../../../../Microchip/MFI/I2C PIC18/I2CStop.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CStop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CStop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CTransmissionHasCompleted.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CTransmissionHasCompleted.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CTransmissionHasCompleted.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CTransmissionHasCompleted.o   "../../../../Microchip/MFI/I2C PIC18/I2CTransmissionHasCompleted.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CTransmissionHasCompleted.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CTransmissionHasCompleted.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CTransmitterIsReady.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CTransmitterIsReady.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CTransmitterIsReady.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CTransmitterIsReady.o   "../../../../Microchip/MFI/I2C PIC18/I2CTransmitterIsReady.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CTransmitterIsReady.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CTransmitterIsReady.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/926214927/MFI_Data.o: ../../../../Microchip/MFI/MFI_Data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/926214927 
	@${RM} ${OBJECTDIR}/_ext/926214927/MFI_Data.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/926214927/MFI_Data.o   ../../../../Microchip/MFI/MFI_Data.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/926214927/MFI_Data.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/926214927/MFI_Data.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/926214927/MFI_iPod_UART.o: ../../../../Microchip/MFI/MFI_iPod_UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/926214927 
	@${RM} ${OBJECTDIR}/_ext/926214927/MFI_iPod_UART.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/926214927/MFI_iPod_UART.o   ../../../../Microchip/MFI/MFI_iPod_UART.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/926214927/MFI_iPod_UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/926214927/MFI_iPod_UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/761559875/mfi_handlers.o: ../UART/mfi_handlers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761559875 
	@${RM} ${OBJECTDIR}/_ext/761559875/mfi_handlers.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/761559875/mfi_handlers.o   ../UART/mfi_handlers.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/761559875/mfi_handlers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761559875/mfi_handlers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2048740170/DebugUARTBuffered.o: ../../../../Microchip/Common/DebugUARTBuffered.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048740170 
	@${RM} ${OBJECTDIR}/_ext/2048740170/DebugUARTBuffered.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2048740170/DebugUARTBuffered.o   ../../../../Microchip/Common/DebugUARTBuffered.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2048740170/DebugUARTBuffered.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048740170/DebugUARTBuffered.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2137914366/LM49450.o: ../PIC18/LM49450.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2137914366 
	@${RM} ${OBJECTDIR}/_ext/2137914366/LM49450.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2137914366/LM49450.o   ../PIC18/LM49450.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2137914366/LM49450.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137914366/LM49450.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2137914366/MCP9800.o: ../PIC18/MCP9800.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2137914366 
	@${RM} ${OBJECTDIR}/_ext/2137914366/MCP9800.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2137914366/MCP9800.o   ../PIC18/MCP9800.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2137914366/MCP9800.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137914366/MCP9800.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/Tick.o: ../Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Tick.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/Tick.o   ../Tick.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2048740170/TimeDelay.o: ../../../../Microchip/Common/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048740170 
	@${RM} ${OBJECTDIR}/_ext/2048740170/TimeDelay.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2048740170/TimeDelay.o   ../../../../Microchip/Common/TimeDelay.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2048740170/TimeDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048740170/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/iPxx.o: ../iPxx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/iPxx.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/iPxx.o   ../iPxx.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/iPxx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/iPxx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2137914366/system.o: ../PIC18/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2137914366 
	@${RM} ${OBJECTDIR}/_ext/2137914366/system.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2137914366/system.o   ../PIC18/system.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2137914366/system.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137914366/system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/debugQueue.o: debugQueue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/debugQueue.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/debugQueue.o   debugQueue.c 
	@${DEP_GEN} -d ${OBJECTDIR}/debugQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/debugQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/_ext/246327853/I2CAcknowledgeByte.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CAcknowledgeByte.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeByte.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeByte.o   "../../../../Microchip/MFI/I2C PIC18/I2CAcknowledgeByte.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeByte.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CAcknowledgeByte.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CAcknowledgeHasCompleted.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CAcknowledgeHasCompleted.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeHasCompleted.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeHasCompleted.o   "../../../../Microchip/MFI/I2C PIC18/I2CAcknowledgeHasCompleted.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CAcknowledgeHasCompleted.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CAcknowledgeHasCompleted.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CBusIsIdle.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CBusIsIdle.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CBusIsIdle.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CBusIsIdle.o   "../../../../Microchip/MFI/I2C PIC18/I2CBusIsIdle.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CBusIsIdle.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CBusIsIdle.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CByteWasAcknowledged.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CByteWasAcknowledged.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CByteWasAcknowledged.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CByteWasAcknowledged.o   "../../../../Microchip/MFI/I2C PIC18/I2CByteWasAcknowledged.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CByteWasAcknowledged.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CByteWasAcknowledged.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CClearStatus.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CClearStatus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CClearStatus.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CClearStatus.o   "../../../../Microchip/MFI/I2C PIC18/I2CClearStatus.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CClearStatus.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CClearStatus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CConfigure.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CConfigure.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CConfigure.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CConfigure.o   "../../../../Microchip/MFI/I2C PIC18/I2CConfigure.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CConfigure.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CConfigure.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CEnable.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CEnable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CEnable.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CEnable.o   "../../../../Microchip/MFI/I2C PIC18/I2CEnable.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CEnable.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CEnable.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CGetByte.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CGetByte.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CGetByte.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CGetByte.o   "../../../../Microchip/MFI/I2C PIC18/I2CGetByte.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CGetByte.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CGetByte.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CGetStatus.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CGetStatus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CGetStatus.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CGetStatus.o   "../../../../Microchip/MFI/I2C PIC18/I2CGetStatus.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CGetStatus.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CGetStatus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CPrivate.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CPrivate.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CPrivate.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CPrivate.o   "../../../../Microchip/MFI/I2C PIC18/I2CPrivate.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CPrivate.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CPrivate.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CReceivedByteIsAnAddress.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CReceivedByteIsAnAddress.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CReceivedByteIsAnAddress.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CReceivedByteIsAnAddress.o   "../../../../Microchip/MFI/I2C PIC18/I2CReceivedByteIsAnAddress.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CReceivedByteIsAnAddress.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CReceivedByteIsAnAddress.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CReceivedDataIsAvailable.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CReceivedDataIsAvailable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CReceivedDataIsAvailable.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CReceivedDataIsAvailable.o   "../../../../Microchip/MFI/I2C PIC18/I2CReceivedDataIsAvailable.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CReceivedDataIsAvailable.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CReceivedDataIsAvailable.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CReceiverEnable.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CReceiverEnable.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CReceiverEnable.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CReceiverEnable.o   "../../../../Microchip/MFI/I2C PIC18/I2CReceiverEnable.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CReceiverEnable.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CReceiverEnable.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CRepeatStart.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CRepeatStart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CRepeatStart.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CRepeatStart.o   "../../../../Microchip/MFI/I2C PIC18/I2CRepeatStart.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CRepeatStart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CRepeatStart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CSendByte.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CSendByte.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CSendByte.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CSendByte.o   "../../../../Microchip/MFI/I2C PIC18/I2CSendByte.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CSendByte.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CSendByte.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CSetFrequencyWithConstant.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CSetFrequencyWithConstant.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CSetFrequencyWithConstant.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CSetFrequencyWithConstant.o   "../../../../Microchip/MFI/I2C PIC18/I2CSetFrequencyWithConstant.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CSetFrequencyWithConstant.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CSetFrequencyWithConstant.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CStart.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CStart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CStart.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CStart.o   "../../../../Microchip/MFI/I2C PIC18/I2CStart.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CStart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CStart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CStop.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CStop.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CStop.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CStop.o   "../../../../Microchip/MFI/I2C PIC18/I2CStop.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CStop.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CStop.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CTransmissionHasCompleted.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CTransmissionHasCompleted.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CTransmissionHasCompleted.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CTransmissionHasCompleted.o   "../../../../Microchip/MFI/I2C PIC18/I2CTransmissionHasCompleted.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CTransmissionHasCompleted.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CTransmissionHasCompleted.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/246327853/I2CTransmitterIsReady.o: ../../../../Microchip/MFI/I2C\ PIC18/I2CTransmitterIsReady.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/246327853 
	@${RM} ${OBJECTDIR}/_ext/246327853/I2CTransmitterIsReady.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/246327853/I2CTransmitterIsReady.o   "../../../../Microchip/MFI/I2C PIC18/I2CTransmitterIsReady.c" 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/246327853/I2CTransmitterIsReady.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/246327853/I2CTransmitterIsReady.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/926214927/MFI_Data.o: ../../../../Microchip/MFI/MFI_Data.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/926214927 
	@${RM} ${OBJECTDIR}/_ext/926214927/MFI_Data.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/926214927/MFI_Data.o   ../../../../Microchip/MFI/MFI_Data.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/926214927/MFI_Data.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/926214927/MFI_Data.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/926214927/MFI_iPod_UART.o: ../../../../Microchip/MFI/MFI_iPod_UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/926214927 
	@${RM} ${OBJECTDIR}/_ext/926214927/MFI_iPod_UART.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/926214927/MFI_iPod_UART.o   ../../../../Microchip/MFI/MFI_iPod_UART.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/926214927/MFI_iPod_UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/926214927/MFI_iPod_UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/761559875/mfi_handlers.o: ../UART/mfi_handlers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/761559875 
	@${RM} ${OBJECTDIR}/_ext/761559875/mfi_handlers.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/761559875/mfi_handlers.o   ../UART/mfi_handlers.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/761559875/mfi_handlers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/761559875/mfi_handlers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2048740170/DebugUARTBuffered.o: ../../../../Microchip/Common/DebugUARTBuffered.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048740170 
	@${RM} ${OBJECTDIR}/_ext/2048740170/DebugUARTBuffered.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2048740170/DebugUARTBuffered.o   ../../../../Microchip/Common/DebugUARTBuffered.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2048740170/DebugUARTBuffered.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048740170/DebugUARTBuffered.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2137914366/LM49450.o: ../PIC18/LM49450.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2137914366 
	@${RM} ${OBJECTDIR}/_ext/2137914366/LM49450.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2137914366/LM49450.o   ../PIC18/LM49450.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2137914366/LM49450.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137914366/LM49450.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2137914366/MCP9800.o: ../PIC18/MCP9800.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2137914366 
	@${RM} ${OBJECTDIR}/_ext/2137914366/MCP9800.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2137914366/MCP9800.o   ../PIC18/MCP9800.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2137914366/MCP9800.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137914366/MCP9800.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/Tick.o: ../Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/Tick.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/Tick.o   ../Tick.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/Tick.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2048740170/TimeDelay.o: ../../../../Microchip/Common/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2048740170 
	@${RM} ${OBJECTDIR}/_ext/2048740170/TimeDelay.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2048740170/TimeDelay.o   ../../../../Microchip/Common/TimeDelay.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2048740170/TimeDelay.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2048740170/TimeDelay.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/iPxx.o: ../iPxx.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/iPxx.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/iPxx.o   ../iPxx.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/iPxx.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/iPxx.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2137914366/system.o: ../PIC18/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/2137914366 
	@${RM} ${OBJECTDIR}/_ext/2137914366/system.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2137914366/system.o   ../PIC18/system.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2137914366/system.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2137914366/system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/debugQueue.o: debugQueue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/debugQueue.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I".." -I"../PIC18" -I"../UART" -I"../../../../Microchip/Include" -I"/C/Program Files/Microchip/mplabc18/v3.38/h" -I"../../../../Microchip/Include/MFI" -I"../../../../Microchip/MFI/I2C PIC18" -I"../../../../Microchip/Include/MFI/I2C PIC18" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/debugQueue.o   debugQueue.c 
	@${DEP_GEN} -d ${OBJECTDIR}/debugQueue.o 
	@${FIXDEPS} "${OBJECTDIR}/debugQueue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/groundStation.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../Microchip/MFI/libMFI_PIC18_SMALL_SINGLE.lib  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -l".."  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_ICD3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}/../lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/groundStation.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}  ../../../../Microchip/MFI/libMFI_PIC18_SMALL_SINGLE.lib 
else
dist/${CND_CONF}/${IMAGE_TYPE}/groundStation.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../Microchip/MFI/libMFI_PIC18_SMALL_SINGLE.lib 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w  -l".."  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}/../lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/groundStation.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}  ../../../../Microchip/MFI/libMFI_PIC18_SMALL_SINGLE.lib 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
