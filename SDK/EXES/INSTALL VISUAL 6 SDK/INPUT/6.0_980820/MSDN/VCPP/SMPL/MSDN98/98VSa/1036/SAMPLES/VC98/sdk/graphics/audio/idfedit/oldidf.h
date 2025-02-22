//************************************************************************
//**
//**  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//**  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//**  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
//**  A PARTICULAR PURPOSE.
//**
//**  Copyright (C) 1993 - 1997 Microsoft Corporation. All Rights Reserved.
//**
//**  IDF.h
//**
//**  DESCRIPTION:
//**     This file contains the format of the .IDF files.
//**
//**  HISTORY:
//**     04/29/93       created.
//**     07/04/93       added UNICODE for displayable strings.
//**     09/04/93       added keymaps.
//**     09/05/93       added ID's for channel types.
//**
//************************************************************************

#if 0

/*
@doc  EXTERNAL SDK

@types   IDFHEADER |
   This is the format of the "hdr " chunk in a Microsoft IDF file.
   This will be the first subchunk of a "MMAP" list chunk.  This will 
   provide information on the IDF itself; what version, who created it,
   and a unique ASCII ID for the instrument.

@field   DWORD | cbStruct |
   This is the inclusive size of the header structure.

@field   DWORD | dwVersion |
   This is the version of the IDF file.
   under.

@field   DWORD | dwCreator |
   This is the creator ID for the IDF.

@field   DWORD | cbInstID |
   This is the size of the unique instrument identifier including the NULL.

@field   BYTE | abInstID[] |
   This is the actual ASCII bytes of the unique instrument id. This _IS_ 
   NULL terminated.  There is no UNICODE version of this since this will
   only be used internally and not displayed to the user.

@othertype  IDFHEADER * | PIDFHEADER |
   A memory model dependant pointer to the structure.

@othertype  IDFHEADER FAR* | LPIDFHEADER |
   A far pointer to the structure.
*/

typedef struct tag_IDFHEADER
{
   DWORD cbStruct;

   DWORD dwVersion;
   DWORD dwCreator;

   DWORD cbInstID;
   BYTE  abInstID[1];
} IDFHEADER, *PIDFHEADER, FAR *LPIDFHEADER;


/*
@doc  EXTERNAL SDK

@types   IDFINSTINFO |
   This is the format of the "inst" chunk in a Microsoft IDF file.
   This chunk will contain information on the instrument, e.g. who
   manufactured it, the name of the instrument, it's manufacturer and
   product id's and a revision number.

@field   DWORD | cbStruct |
   This is the inclusive size of the instrument information structure.

@field   DWORD | dwManufactID |
   Manufacturer's ID.

@field   DWORD | dwProductID |
   Product's ID.

@field   DWORD | dwRevision |
   Revision of the product.

@field   DWORD | cbManufactASCII |
   Length of the ASCII version of the manufacturuers name.

@field   DWORD | cbManufactUNICODE |
   Length of the UNICODE version of the manufacturuers name.

@field   DWORD | cbProductASCII |
   Length of the ASCII version of the product name.

@field   DWORD | cbProductUNICODE |
   Length of the UNICODE version of the product name.

@field   BYTE | abData[] |
   Contains the ASCII and UNICODE strings for the manufacturer and product
   names.  NOTE that all strings are separated by a NULL and the NULL IS
   counted in the string lengths.

@othertype  IDFINSTINFO * | PIDFINSTINFO |
   A memory model dependant pointer to the structure.

@othertype  IDFINSTINFO FAR * | LPIDFINSTINFO |
   A far pointer to the structure.

@comm The idea is that the cbManufactXXXXX and cbProductXXXXX will be the
      offsets into the bData array of bytes and it will contain a complete
      string that you can strcpy out.  That is why the NULL is included in
      the byte count and in the actual data.
*/

typedef struct tag_IDFINSTINFO
{
   DWORD cbStruct;

   DWORD dwManufactID;
   DWORD dwProductID;
   DWORD dwRevision;

   DWORD cbManufactASCII;
   DWORD cbManufactUNICODE;
   DWORD cbProductASCII;
   DWORD cbProductUNICODE;

   BYTE  abData[1];
} IDFINSTINFO, FAR *LPIDFINSTINFO;

/*
@doc  EXTERNAL SDK

@types   IDFINSTCAPS |
   This is the format of the "caps" chunk in a Microsoft IDF file.
   This chunk will contain information on the MIDI capabilities of
   the device. e.g. basic channel of the instrument, number of channels
   that the instrument has available. the polyphony of the instrument, 
   whether or not it supports General MIDI, etc....

@field   DWORD | cbStruct |
   This is the size of the capabilities structure.

@field   DWORD | fdwFlags |
   Flags specifiying additional capabilities of an instrument.

@flag IDFINSTCAPS_F_GENERAL_MIDI |
   Instrument supports General MIDI.

@flag IDFINSTCAPS_F_SYSTEMEXCLUSIVE |
   Instrument supports system exclusive messages

@field   DWORD | dwBasicChannel |
   The basic channel for the instrument.

@field   DWORD | cNumChannels |
   Number of channels that the instrument supports to.

@field   DWORD | cInstrumentPolyphony |
   The total polyphony for the instrument.

@field   DWORD | cChannelPolyphony |
   The polyphony per channel.

@othertype  IDFINSTCAPS * | PIDFINSTCAPS |
   A memory model dependant pointer to the structure.

@othertype  IDFINSTCAPS FAR * | LPIDFINSTCAPS |
   A far pointer to the structure.
*/

typedef struct tag_IDFINSTCAPS
{
   DWORD cbStruct;
   DWORD fdwFlags;
   DWORD dwBasicChannel;
   DWORD cNumChannels;
   DWORD cInstrumentPolyphony;
   DWORD cChannelPolyphony;
} IDFINSTCAPS, *PIDFINSTCAPS, FAR *LPIDFINSTCAPS;

#define  IDFINSTCAPS_F_GENERAL_MIDI       0x00000001
#define  IDFINSTCAPS_F_SYSTEMEXCLUSIVE    0x00000002

#endif

/*
@doc  EXTERNAL SDK

@types   IDFCHNLHDR |
   This is the format of the "chnl" chunk in a Microsoft IDF file.
   This contains a description on what "type" a channel is, i.e. 
   is it a General MIDI channel, a drum channel, etc... Directly 
   following this header is the actual data on each channel.

@field   DWORD | cbStruct |
   This is the size of the channel header structure.

@field   DWORD | fdwFlags |
   Flags describing the channel type information.

@flag IDFCHNLHDR_F_GENERAL_MIDI |
   If this flag is set then any channels that are not defined in the 
   IDF are General MIDI channel types.  If this flag is _NOT_ set then
   any channels that are not defined in the IDF are undefined and should 
   NOT be used in mapping.

@field   DWORD | cNumChannels |
   This is the number of channels that follows the header.

@othertype  IDFCHNLHDR * | PIDFCHNLHDR |
   A memory model dependant pointer to the structure.

@othertype  IDFCHNLHDR FAR * | LPIDFCHNLHDR |
   A far pointer to the structure.
*/


typedef struct tag_IDFCHNLHDR
{
   DWORD cbStruct;

   DWORD cNumChannels;
   DWORD fdwFlags;
} IDFCHNLHDR, *PIDFCHNLHDR, FAR *LPIDFCHNLHDR;

#define  IDFCHNLHDR_F_GENERAL_MIDI     0x00000001


/*
@doc  EXTERNAL SDK

@types    IDFCHNLINFO |
   This is the format of the actual channel information for Microsoft
   authored IDF files. This is the Microsoft supported format for
   channel information.

@field   DWORD | dwChannel |
   This is the channel number that the structure defines.

@field   DWORD | fdwChannel |
   Defines the possible types this channel can be.

   @flag    IDFCHNLINFO_F_GENERAL_CHANNEL |
       Indicates that this channel may be a general channel.

   @flag    IDFCHNLINFO_F_DRUM_CHANNEL |
       Indicates that this channel may be a drum channel.

@field   DWORD | cbGeneralInitData |
    Specifies the length of the data which should be sent to initialize
    the channel to a general channel. This data will be sent whenever the
    channel is allocated as a general channel. If no initialization data
    is desired, this field should be set to zero. If more than one channel
    type is specified in the <f fdwChannel> field, initialization data
    must be specified and this field may not be zero.

@field   DWORD | cbDrumInitData |
    Specifies the length of the data which should be sent to initialize
    the channel to a drum channel. This data will be sent whenever the
    channel is allocated as a drum channel. If no initialization data
    is desired, this field should be set to zero. If more than one channel
    type is specified in the <f fdwChannel> field, initialization data
    must be specified and this field may not be zero.


@field    BYTE | abData[] |
    This field contains the actual initialization data to set the channel
    to general or drum. <f abData> contains first the initialization
    sequence to set the channel to a general channel, followed by
    the sequence to initialize the channel to a drum channel.
    <f cbGeneralInitData> and <f cbDrumInitData> should indicate the lengths
    of these sequences, byte aligned. However, the actual sequence should
    be padded so that it is actually DWORD aligned (i.e. even multiple
    of four bytes). <f cbStruct> should reflect the padded length of
    the sequences.
        
@othertype  IDFCHNLINFO * | PIDFCHNLINFO |
   A memory model dependant pointer to the structure.

@othertype  IDFCHNLINFO FAR * | LPIDFCHNLINFO |
   A far pointer to the structure.
*/

typedef struct tag_IDFCHNLINFO
{
   DWORD cbStruct;

   DWORD dwChannel;
   DWORD fdwChannel;

   DWORD cbGeneralInitData;
   DWORD cbDrumInitData;

   BYTE  abData[];

} IDFCHNLINFO, *PIDFCHNLINFO, FAR *LPIDFCHNLINFO;


//
// Currently defined channel types.
//
#define  IDFCHNLINFO_F_GENERAL_CHANNEL      0x00000001
#define  IDFCHNLINFO_F_DRUM_CHANNEL         0x00000002

#if 0

/*
@doc  EXTERNAL SDK

@types   IDFPATCHMAPHDR |
   This is the format of the "map " chunk in a Microsoft IDF file.
   This chunk contains information on the patch map used for the 
   instrument. Directly following this header is the actual mapping 
   information for each patch.

@field   DWORD | cbStruct |
   This is the size of the patch map header structure.

@field   BYTE | abPatchMap[128] |
   This array contains the actual patch map. The incoming patch is
   used to index the array; the array contents are the new patch value
   and must be in the range 0x00-0x7F. Patch maps will only apply to
   channels of type general. If the instrument needs a patch change
   on a drum channel, it should be included in the initialization data
   in the IDFCHANNELINFO.

@othertype  IDFPATCHMAPHDR * | PIDFPATCHMAPHDR |
   A memory model dependant pointer to the structure.

@othertype  IDFPATCHMAPHDR FAR * | LPIDFPATCHMAPHDR |
   A far pointer to the structure.
*/

typedef struct tag_IDFPATCHMAPHDR
{
   DWORD cbStruct;
   BYTE  abPatchMap[128];
           
} IDFPATCHMAPHDR, *PIDFPATCHMAPHDR, FAR *LPIDFPATCHMAPHDR;

#endif // 0

/*
@doc  EXTERNAL SDK

@types   IDFKEYHDR |
   This is the format of the "key " chunk in a Microsoft IDF file.
   This chunk contains information on the all of the key maps used 
   for a given instrument. The information that is in this structure
   pertains to all of the key maps for the instrument.  It contains
   the total number of key maps for the instrument and whether or not
   the key maps are General MIDI.

@field   DWORD | cbStruct |
   This is the size of the key map header structure.

@field   DWORD | cNumKeyMaps |
   This is the number of key maps that follow the header.

@field   DWORD | cbKeyMap |
   This is the size of each key map that follows the header.   

@othertype  IDFPATCHMAPHDR * | PIDFPATCHMAPHDR |
   A memory model dependant pointer to the structure.

@othertype  IDFPATCHMAPHDR FAR * | LPIDFPATCHMAPHDR |
   A far pointer to the structure.
*/

typedef struct tag_IDFKEYHDR
{
   DWORD cbStruct;
   DWORD cNumKeyMaps;
   DWORD cbKeyMap;
} IDFKEYHDR, *PIDFKEYHDR, FAR *LPIDFKEYHDR;

/*
@doc  EXTERNAL SDK

@types   IDFKEY |
   This is a keymap that follows the key map header. 

@field   DWORD | cbStruct |
   This is the size of the key map header structure.

@field   DWORD | fdwKeyMapType |
   This field specifies the channel type this key map is valid for.

@flag IDFKEY_F_GENERAL_CHANNEL      0x00000001
@flag IDFKEY_F_DRUM_CHANNEL         0x00000002

@field   BYTE | abKeyMap[128] |
    This field contains the actual key map. The incoming key number from
    a note on or note off message is used to index this array; the array
    contents are the new key value. If the high bit it set in the new
    key value, then the note on or note off will be ignore; otherwise,
    it will be transmitted with the new key value.
    
@othertype  IDFKEY * | PIDFKEY |
   A memory model dependant pointer to the structure.

@othertype  IDFKEY FAR * | LPIDFKEY |
   A far pointer to the structure.
*/

typedef struct tag_IDFKEY
{
   DWORD cbStruct;
   DWORD fdwKeyMap;
   BYTE  abKeyMap[128];
} IDFKEY, *PIDFKEY, FAR *LPIDFKEY;

#define IDFKEY_F_GENERAL_CHANNEL      0x00000001L
#define IDFKEY_F_DRUM_CHANNEL         0x00000002L
