#include "descriptor.h"

/*see EN_300 468 chapter 6*/

/*adaptation_field_data_descriptor*/
struct adaptation_field_data_identifier
{
	uint8_t announcement_switching_data:1;
	uint8_t AU_information_data:1;
	uint8_t PVR_assist_information_data:1;
	uint8_t tsap_timeline:1;
	uint8_t reserved:4;
};
/*ancillary_data_descriptor*/
struct ancillary_data_identifier
{
	uint8_t DVD_video_ancillary_data:1;
	uint8_t extended_ancillary_data:1;
	uint8_t announcement_switching_data:1;
	uint8_t DAB_ancillary_data:1;
	uint8_t scale_factor_error_check:1;
	uint8_t MPEG4_ancillary_data:1;
	uint8_t RDS_via_UECP:1;
	uint8_t reserved:1;
};

/*Announcement support descriptor*/
struct announcement_support_indicator{
	uint16_t emergency_alarm:1;
	uint16_t road_traffic_flash:1;
	uint16_t public_transport_flash:1;
	uint16_t warning_message:1;
	uint16_t news_flash:1;
	uint16_t weather_flash:1;
	uint16_t event_announcement:1;
	uint16_t personal_call:1;
	uint16_t reserved:8;
};

struct ISO_639_Language_descriptor{

};

struct component_descriptor{ 
	uint8_t descriptor_tag;
	uint8_t descriptor_length;
	uint8_t stream_content_ext:4; 
	uint8_t stream_content:4;
	uint8_t component_type;
	uint32_t component_tag:8; 
	uint32_t ISO_639_language_code:24; 
	uint8_t data[0];
};

static void DumpMaxBitrateDescriptor(dvbpsi_max_bitrate_dr_t* bitrate_descriptor)
{  
    printf( "Bitrate: %d\n", bitrate_descriptor->i_max_bitrate);
}


static void DumpSystemClockDescriptor(dvbpsi_system_clock_dr_t* p_clock_descriptor)
{  
    printf( "External clock: %s, Accuracy: %E\n", p_clock_descriptor->b_external_clock_ref ? "Yes" : "No",     p_clock_descriptor->i_clock_accuracy_integer *     pow(10.0, -(double)p_clock_descriptor->i_clock_accuracy_exponent));
}


static void DumpStreamIdentifierDescriptor(dvbpsi_stream_identifier_dr_t* p_si_descriptor)
{  
    printf( "Component tag: %d\n", p_si_descriptor->i_component_tag);
}

static void DumpSubtitleDescriptor(dvbpsi_subtitling_dr_t* p_subtitle_descriptor)
{  
    int a; 
    printf("%d subtitles,\n", p_subtitle_descriptor->i_subtitles_number);  
    for (a = 0; a < p_subtitle_descriptor->i_subtitles_number; ++a)    
    {
        printf( "       | %d - lang: %c%c%c, type: %d, cpid: %d, apid: %d\n", a,         p_subtitle_descriptor->p_subtitle[a].i_iso6392_language_code[0],         p_subtitle_descriptor->p_subtitle[a].i_iso6392_language_code[1],         p_subtitle_descriptor->p_subtitle[a].i_iso6392_language_code[2],         p_subtitle_descriptor->p_subtitle[a].i_subtitling_type,         p_subtitle_descriptor->p_subtitle[a].i_composition_page_id,         p_subtitle_descriptor->p_subtitle[a].i_ancillary_page_id);    
    }
}


static void DumpDescriptors(const char* str, descriptor_t* p_descriptor)
{
    int i;
    while(p_descriptor)
    {
        printf( "%s 0x%02x : ", str, p_descriptor->tag);
        switch (p_descriptor->tag)
        {
            case SYSTEM_CLOCK_DR:
                DumpSystemClockDescriptor(dvbpsi_DecodeSystemClockDr(p_descriptor));
                break;
            case MAX_BITRATE_DR:
                DumpMaxBitrateDescriptor(dvbpsi_DecodeMaxBitrateDr(p_descriptor));         
                break;
            case STREAM_IDENTIFIER_DR:
                DumpStreamIdentifierDescriptor(dvbpsi_DecodeStreamIdentifierDr(p_descriptor));     
                break;
            case SUBTITLING_DR:
                DumpSubtitleDescriptor(dvbpsi_DecodeSubtitlingDr(p_descriptor));      
                break;
            default:
                printf(  "\"");
                for(i = 0; i < p_descriptor->i_length; i++)
                    printf(  "%c", p_descriptor->p_data[i]);
                printf( "\"\n");
        }
        p_descriptor = p_descriptor->p_next;
    }
}

