/* ***********************************************************
 * This file was automatically generated on 2021-11-29.      *
 *                                                           *
 * C/C++ for Microcontrollers Bindings Version 2.0.0         *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/


#include "bricklet_piezo_speaker_v2.h"
#include "base58.h"
#include "endian_convert.h"
#include "errors.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif


#if TF_IMPLEMENT_CALLBACKS != 0
static bool tf_piezo_speaker_v2_callback_handler(void *device, uint8_t fid, TF_PacketBuffer *payload) {
    TF_PiezoSpeakerV2 *piezo_speaker_v2 = (TF_PiezoSpeakerV2 *)device;
    TF_HALCommon *hal_common = tf_hal_get_common(piezo_speaker_v2->tfp->spitfp->hal);
    (void)payload;

    switch (fid) {
        case TF_PIEZO_SPEAKER_V2_CALLBACK_BEEP_FINISHED: {
            TF_PiezoSpeakerV2_BeepFinishedHandler fn = piezo_speaker_v2->beep_finished_handler;
            void *user_data = piezo_speaker_v2->beep_finished_user_data;
            if (fn == NULL) {
                return false;
            }


            hal_common->locked = true;
            fn(piezo_speaker_v2, user_data);
            hal_common->locked = false;
            break;
        }

        case TF_PIEZO_SPEAKER_V2_CALLBACK_ALARM_FINISHED: {
            TF_PiezoSpeakerV2_AlarmFinishedHandler fn = piezo_speaker_v2->alarm_finished_handler;
            void *user_data = piezo_speaker_v2->alarm_finished_user_data;
            if (fn == NULL) {
                return false;
            }


            hal_common->locked = true;
            fn(piezo_speaker_v2, user_data);
            hal_common->locked = false;
            break;
        }

        default:
            return false;
    }

    return true;
}
#else
static bool tf_piezo_speaker_v2_callback_handler(void *device, uint8_t fid, TF_PacketBuffer *payload) {
    return false;
}
#endif
int tf_piezo_speaker_v2_create(TF_PiezoSpeakerV2 *piezo_speaker_v2, const char *uid_or_port_name, TF_HAL *hal) {
    if (piezo_speaker_v2 == NULL || hal == NULL) {
        return TF_E_NULL;
    }

    memset(piezo_speaker_v2, 0, sizeof(TF_PiezoSpeakerV2));

    TF_TFP *tfp;
    int rc = tf_hal_get_attachable_tfp(hal, &tfp, uid_or_port_name, TF_PIEZO_SPEAKER_V2_DEVICE_IDENTIFIER);

    if (rc != TF_E_OK) {
        return rc;
    }

    piezo_speaker_v2->tfp = tfp;
    piezo_speaker_v2->tfp->device = piezo_speaker_v2;
    piezo_speaker_v2->tfp->cb_handler = tf_piezo_speaker_v2_callback_handler;
    piezo_speaker_v2->response_expected[0] = 0x00;

    return TF_E_OK;
}

int tf_piezo_speaker_v2_destroy(TF_PiezoSpeakerV2 *piezo_speaker_v2) {
    if (piezo_speaker_v2 == NULL || piezo_speaker_v2->tfp == NULL) {
        return TF_E_NULL;
    }

    piezo_speaker_v2->tfp->cb_handler = NULL;
    piezo_speaker_v2->tfp->device = NULL;
    piezo_speaker_v2->tfp = NULL;

    return TF_E_OK;
}

int tf_piezo_speaker_v2_get_response_expected(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint8_t function_id, bool *ret_response_expected) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    switch (function_id) {
        case TF_PIEZO_SPEAKER_V2_FUNCTION_SET_BEEP:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (piezo_speaker_v2->response_expected[0] & (1 << 0)) != 0;
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_SET_ALARM:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (piezo_speaker_v2->response_expected[0] & (1 << 1)) != 0;
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_UPDATE_VOLUME:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (piezo_speaker_v2->response_expected[0] & (1 << 2)) != 0;
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_UPDATE_FREQUENCY:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (piezo_speaker_v2->response_expected[0] & (1 << 3)) != 0;
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (piezo_speaker_v2->response_expected[0] & (1 << 4)) != 0;
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_SET_STATUS_LED_CONFIG:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (piezo_speaker_v2->response_expected[0] & (1 << 5)) != 0;
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_RESET:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (piezo_speaker_v2->response_expected[0] & (1 << 6)) != 0;
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_WRITE_UID:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (piezo_speaker_v2->response_expected[0] & (1 << 7)) != 0;
            }
            break;
        default:
            return TF_E_INVALID_PARAMETER;
    }

    return TF_E_OK;
}

int tf_piezo_speaker_v2_set_response_expected(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint8_t function_id, bool response_expected) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    switch (function_id) {
        case TF_PIEZO_SPEAKER_V2_FUNCTION_SET_BEEP:
            if (response_expected) {
                piezo_speaker_v2->response_expected[0] |= (1 << 0);
            } else {
                piezo_speaker_v2->response_expected[0] &= ~(1 << 0);
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_SET_ALARM:
            if (response_expected) {
                piezo_speaker_v2->response_expected[0] |= (1 << 1);
            } else {
                piezo_speaker_v2->response_expected[0] &= ~(1 << 1);
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_UPDATE_VOLUME:
            if (response_expected) {
                piezo_speaker_v2->response_expected[0] |= (1 << 2);
            } else {
                piezo_speaker_v2->response_expected[0] &= ~(1 << 2);
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_UPDATE_FREQUENCY:
            if (response_expected) {
                piezo_speaker_v2->response_expected[0] |= (1 << 3);
            } else {
                piezo_speaker_v2->response_expected[0] &= ~(1 << 3);
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER:
            if (response_expected) {
                piezo_speaker_v2->response_expected[0] |= (1 << 4);
            } else {
                piezo_speaker_v2->response_expected[0] &= ~(1 << 4);
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_SET_STATUS_LED_CONFIG:
            if (response_expected) {
                piezo_speaker_v2->response_expected[0] |= (1 << 5);
            } else {
                piezo_speaker_v2->response_expected[0] &= ~(1 << 5);
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_RESET:
            if (response_expected) {
                piezo_speaker_v2->response_expected[0] |= (1 << 6);
            } else {
                piezo_speaker_v2->response_expected[0] &= ~(1 << 6);
            }
            break;
        case TF_PIEZO_SPEAKER_V2_FUNCTION_WRITE_UID:
            if (response_expected) {
                piezo_speaker_v2->response_expected[0] |= (1 << 7);
            } else {
                piezo_speaker_v2->response_expected[0] &= ~(1 << 7);
            }
            break;
        default:
            return TF_E_INVALID_PARAMETER;
    }

    return TF_E_OK;
}

int tf_piezo_speaker_v2_set_response_expected_all(TF_PiezoSpeakerV2 *piezo_speaker_v2, bool response_expected) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    memset(piezo_speaker_v2->response_expected, response_expected ? 0xFF : 0, 1);

    return TF_E_OK;
}

int tf_piezo_speaker_v2_set_beep(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint16_t frequency, uint8_t volume, uint32_t duration) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_piezo_speaker_v2_get_response_expected(piezo_speaker_v2, TF_PIEZO_SPEAKER_V2_FUNCTION_SET_BEEP, &_response_expected);
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_SET_BEEP, 7, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(piezo_speaker_v2->tfp);

    frequency = tf_leconvert_uint16_to(frequency); memcpy(_send_buf + 0, &frequency, 2);
    _send_buf[2] = (uint8_t)volume;
    duration = tf_leconvert_uint32_to(duration); memcpy(_send_buf + 3, &duration, 4);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_get_beep(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint16_t *ret_frequency, uint8_t *ret_volume, uint32_t *ret_duration, uint32_t *ret_duration_remaining) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_GET_BEEP, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(piezo_speaker_v2->tfp);
        if (_error_code != 0 || _length != 11) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_frequency != NULL) { *ret_frequency = tf_packet_buffer_read_uint16_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 2); }
            if (ret_volume != NULL) { *ret_volume = tf_packet_buffer_read_uint8_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
            if (ret_duration != NULL) { *ret_duration = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
            if (ret_duration_remaining != NULL) { *ret_duration_remaining = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
        }
        tf_tfp_packet_processed(piezo_speaker_v2->tfp);
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 11) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_set_alarm(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint16_t start_frequency, uint16_t end_frequency, uint16_t step_size, uint16_t step_delay, uint8_t volume, uint32_t duration) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_piezo_speaker_v2_get_response_expected(piezo_speaker_v2, TF_PIEZO_SPEAKER_V2_FUNCTION_SET_ALARM, &_response_expected);
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_SET_ALARM, 13, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(piezo_speaker_v2->tfp);

    start_frequency = tf_leconvert_uint16_to(start_frequency); memcpy(_send_buf + 0, &start_frequency, 2);
    end_frequency = tf_leconvert_uint16_to(end_frequency); memcpy(_send_buf + 2, &end_frequency, 2);
    step_size = tf_leconvert_uint16_to(step_size); memcpy(_send_buf + 4, &step_size, 2);
    step_delay = tf_leconvert_uint16_to(step_delay); memcpy(_send_buf + 6, &step_delay, 2);
    _send_buf[8] = (uint8_t)volume;
    duration = tf_leconvert_uint32_to(duration); memcpy(_send_buf + 9, &duration, 4);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_get_alarm(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint16_t *ret_start_frequency, uint16_t *ret_end_frequency, uint16_t *ret_step_size, uint16_t *ret_step_delay, uint8_t *ret_volume, uint32_t *ret_duration, uint32_t *ret_duration_remaining, uint16_t *ret_current_frequency) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_GET_ALARM, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(piezo_speaker_v2->tfp);
        if (_error_code != 0 || _length != 19) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_start_frequency != NULL) { *ret_start_frequency = tf_packet_buffer_read_uint16_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 2); }
            if (ret_end_frequency != NULL) { *ret_end_frequency = tf_packet_buffer_read_uint16_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 2); }
            if (ret_step_size != NULL) { *ret_step_size = tf_packet_buffer_read_uint16_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 2); }
            if (ret_step_delay != NULL) { *ret_step_delay = tf_packet_buffer_read_uint16_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 2); }
            if (ret_volume != NULL) { *ret_volume = tf_packet_buffer_read_uint8_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
            if (ret_duration != NULL) { *ret_duration = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
            if (ret_duration_remaining != NULL) { *ret_duration_remaining = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
            if (ret_current_frequency != NULL) { *ret_current_frequency = tf_packet_buffer_read_uint16_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 2); }
        }
        tf_tfp_packet_processed(piezo_speaker_v2->tfp);
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 19) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_update_volume(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint8_t volume) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_piezo_speaker_v2_get_response_expected(piezo_speaker_v2, TF_PIEZO_SPEAKER_V2_FUNCTION_UPDATE_VOLUME, &_response_expected);
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_UPDATE_VOLUME, 1, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(piezo_speaker_v2->tfp);

    _send_buf[0] = (uint8_t)volume;

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_update_frequency(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint16_t frequency) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_piezo_speaker_v2_get_response_expected(piezo_speaker_v2, TF_PIEZO_SPEAKER_V2_FUNCTION_UPDATE_FREQUENCY, &_response_expected);
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_UPDATE_FREQUENCY, 2, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(piezo_speaker_v2->tfp);

    frequency = tf_leconvert_uint16_to(frequency); memcpy(_send_buf + 0, &frequency, 2);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_get_spitfp_error_count(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(piezo_speaker_v2->tfp);
        if (_error_code != 0 || _length != 16) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_error_count_ack_checksum != NULL) { *ret_error_count_ack_checksum = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
            if (ret_error_count_message_checksum != NULL) { *ret_error_count_message_checksum = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
            if (ret_error_count_frame != NULL) { *ret_error_count_frame = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
            if (ret_error_count_overflow != NULL) { *ret_error_count_overflow = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
        }
        tf_tfp_packet_processed(piezo_speaker_v2->tfp);
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 16) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_set_bootloader_mode(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint8_t mode, uint8_t *ret_status) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_SET_BOOTLOADER_MODE, 1, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(piezo_speaker_v2->tfp);

    _send_buf[0] = (uint8_t)mode;

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(piezo_speaker_v2->tfp);
        if (_error_code != 0 || _length != 1) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_status != NULL) { *ret_status = tf_packet_buffer_read_uint8_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
        }
        tf_tfp_packet_processed(piezo_speaker_v2->tfp);
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 1) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_get_bootloader_mode(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint8_t *ret_mode) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_GET_BOOTLOADER_MODE, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(piezo_speaker_v2->tfp);
        if (_error_code != 0 || _length != 1) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_mode != NULL) { *ret_mode = tf_packet_buffer_read_uint8_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
        }
        tf_tfp_packet_processed(piezo_speaker_v2->tfp);
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 1) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_set_write_firmware_pointer(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint32_t pointer) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_piezo_speaker_v2_get_response_expected(piezo_speaker_v2, TF_PIEZO_SPEAKER_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, &_response_expected);
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, 4, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(piezo_speaker_v2->tfp);

    pointer = tf_leconvert_uint32_to(pointer); memcpy(_send_buf + 0, &pointer, 4);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_write_firmware(TF_PiezoSpeakerV2 *piezo_speaker_v2, const uint8_t data[64], uint8_t *ret_status) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_WRITE_FIRMWARE, 64, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(piezo_speaker_v2->tfp);

    memcpy(_send_buf + 0, data, 64);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(piezo_speaker_v2->tfp);
        if (_error_code != 0 || _length != 1) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_status != NULL) { *ret_status = tf_packet_buffer_read_uint8_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
        }
        tf_tfp_packet_processed(piezo_speaker_v2->tfp);
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 1) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_set_status_led_config(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint8_t config) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_piezo_speaker_v2_get_response_expected(piezo_speaker_v2, TF_PIEZO_SPEAKER_V2_FUNCTION_SET_STATUS_LED_CONFIG, &_response_expected);
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_SET_STATUS_LED_CONFIG, 1, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(piezo_speaker_v2->tfp);

    _send_buf[0] = (uint8_t)config;

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_get_status_led_config(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint8_t *ret_config) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_GET_STATUS_LED_CONFIG, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(piezo_speaker_v2->tfp);
        if (_error_code != 0 || _length != 1) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_config != NULL) { *ret_config = tf_packet_buffer_read_uint8_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
        }
        tf_tfp_packet_processed(piezo_speaker_v2->tfp);
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 1) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_get_chip_temperature(TF_PiezoSpeakerV2 *piezo_speaker_v2, int16_t *ret_temperature) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_GET_CHIP_TEMPERATURE, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(piezo_speaker_v2->tfp);
        if (_error_code != 0 || _length != 2) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_temperature != NULL) { *ret_temperature = tf_packet_buffer_read_int16_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 2); }
        }
        tf_tfp_packet_processed(piezo_speaker_v2->tfp);
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 2) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_reset(TF_PiezoSpeakerV2 *piezo_speaker_v2) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_piezo_speaker_v2_get_response_expected(piezo_speaker_v2, TF_PIEZO_SPEAKER_V2_FUNCTION_RESET, &_response_expected);
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_RESET, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_write_uid(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint32_t uid) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_piezo_speaker_v2_get_response_expected(piezo_speaker_v2, TF_PIEZO_SPEAKER_V2_FUNCTION_WRITE_UID, &_response_expected);
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_WRITE_UID, 4, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(piezo_speaker_v2->tfp);

    uid = tf_leconvert_uint32_to(uid); memcpy(_send_buf + 0, &uid, 4);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_read_uid(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint32_t *ret_uid) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_READ_UID, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(piezo_speaker_v2->tfp);
        if (_error_code != 0 || _length != 4) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_uid != NULL) { *ret_uid = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
        }
        tf_tfp_packet_processed(piezo_speaker_v2->tfp);
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 4) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_piezo_speaker_v2_get_identity(TF_PiezoSpeakerV2 *piezo_speaker_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *_hal = piezo_speaker_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(piezo_speaker_v2->tfp, TF_PIEZO_SPEAKER_V2_FUNCTION_GET_IDENTITY, 0, _response_expected);

    size_t _i;
    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(piezo_speaker_v2->tfp, _response_expected, _deadline, &_error_code, &_length);

    if (_result < 0) {
        return _result;
    }

    if (_result & TF_TICK_TIMEOUT) {
        return TF_E_TIMEOUT;
    }

    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(piezo_speaker_v2->tfp);
        if (_error_code != 0 || _length != 25) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_uid != NULL) { tf_packet_buffer_pop_n(_recv_buf, (uint8_t *)ret_uid, 8);} else { tf_packet_buffer_remove(_recv_buf, 8); }
            if (ret_connected_uid != NULL) { tf_packet_buffer_pop_n(_recv_buf, (uint8_t *)ret_connected_uid, 8);} else { tf_packet_buffer_remove(_recv_buf, 8); }
            if (ret_position != NULL) { *ret_position = tf_packet_buffer_read_char(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
            if (ret_hardware_version != NULL) { for (_i = 0; _i < 3; ++_i) ret_hardware_version[_i] = tf_packet_buffer_read_uint8_t(_recv_buf);} else { tf_packet_buffer_remove(_recv_buf, 3); }
            if (ret_firmware_version != NULL) { for (_i = 0; _i < 3; ++_i) ret_firmware_version[_i] = tf_packet_buffer_read_uint8_t(_recv_buf);} else { tf_packet_buffer_remove(_recv_buf, 3); }
            if (ret_device_identifier != NULL) { *ret_device_identifier = tf_packet_buffer_read_uint16_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 2); }
        }
        tf_tfp_packet_processed(piezo_speaker_v2->tfp);
    }

    _result = tf_tfp_finish_send(piezo_speaker_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 25) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}
#if TF_IMPLEMENT_CALLBACKS != 0
int tf_piezo_speaker_v2_register_beep_finished_callback(TF_PiezoSpeakerV2 *piezo_speaker_v2, TF_PiezoSpeakerV2_BeepFinishedHandler handler, void *user_data) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    if (handler == NULL) {
        piezo_speaker_v2->tfp->needs_callback_tick = false;
        piezo_speaker_v2->tfp->needs_callback_tick |= piezo_speaker_v2->alarm_finished_handler != NULL;
    } else {
        piezo_speaker_v2->tfp->needs_callback_tick = true;
    }

    piezo_speaker_v2->beep_finished_handler = handler;
    piezo_speaker_v2->beep_finished_user_data = user_data;

    return TF_E_OK;
}


int tf_piezo_speaker_v2_register_alarm_finished_callback(TF_PiezoSpeakerV2 *piezo_speaker_v2, TF_PiezoSpeakerV2_AlarmFinishedHandler handler, void *user_data) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    if (handler == NULL) {
        piezo_speaker_v2->tfp->needs_callback_tick = false;
        piezo_speaker_v2->tfp->needs_callback_tick |= piezo_speaker_v2->beep_finished_handler != NULL;
    } else {
        piezo_speaker_v2->tfp->needs_callback_tick = true;
    }

    piezo_speaker_v2->alarm_finished_handler = handler;
    piezo_speaker_v2->alarm_finished_user_data = user_data;

    return TF_E_OK;
}
#endif
int tf_piezo_speaker_v2_callback_tick(TF_PiezoSpeakerV2 *piezo_speaker_v2, uint32_t timeout_us) {
    if (piezo_speaker_v2 == NULL) {
        return TF_E_NULL;
    }

    TF_HAL *hal = piezo_speaker_v2->tfp->spitfp->hal;

    return tf_tfp_callback_tick(piezo_speaker_v2->tfp, tf_hal_current_time_us(hal) + timeout_us);
}

#ifdef __cplusplus
}
#endif
