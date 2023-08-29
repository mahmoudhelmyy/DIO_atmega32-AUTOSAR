1. Values used by the DIO Driver for the software level of Channels are either STD_HIGH or STD_LOW.
2. A general-purpose digital IO pin represents a DIO channel.
3. The Port module shall configure a DIO channel as input or output.
4. A channel group is a formal logical combination of several adjoining DIO channels within a DIO port
for Example: Dio_WriteChannelGroup(ChannelGroupIdPtr, Level)

5. DIO services: - read or write >> port, channel and channel group.
6. All read and write functions of the Dio module shall be re-entrant. 
Reason: The DIO Driver may be accessed by different upper layer handlers or 
drivers. These upper layer modules may access the driver concurrently.
7. The DIO module shall perform Inter Module Checks to avoid integration of incompatible files.

The following version numbers shall be verified: 
 <MODULENAME>_AR_RELEASE_MAJOR_VERSION >> Dio_AR_RELEASE_MAJOR_VERSION
 <MODULENAME>_AR_RELEASE_MINOR_VERSION >> Dio_AR_RELEASE_MINOR_VERSION
Where <MODULENAME> is the module abbreviation of the other (external) modules 
which provide header files included by DIO module. 
If the values are not identical to the expected values, an error shall be reported

8. Initialization of the hardware is done by the PORT Driver. 
9. Runtime reconfiguration is provided by the PORT Driver.
10. The PORT driver shall provide the reconfiguration of the port pin direction 
during runtime.

/* This is used to define the abstraction of compiler keyword static */
#define STATIC            static

/*The Dio_Init function shall initialize all global variables of the DIO module*/
STATIC const Dio_ConfigType *Dio_PortPins = NULL_PTR;
STATIC uint8 Dio_Status = DIO_NOT_INITIALIZED;
