/* ***********************************************************
 * This file was automatically generated on 2023-01-25.      *
 *                                                           *
 * C/C++ for Microcontrollers Bindings Version 2.0.3         *
 *                                                           *
 * If you have a bugfix for this file and want to commit it, *
 * please fix the bug in the generator. You can find a link  *
 * to the generators git repository on tinkerforge.com       *
 *************************************************************/


#include "bricklet_multi_touch_v2.h"
#include "base58.h"
#include "endian_convert.h"
#include "errors.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif


#if TF_IMPLEMENT_CALLBACKS != 0
static bool tf_multi_touch_v2_callback_handler(void *device, uint8_t fid, TF_PacketBuffer *payload) {
    TF_MultiTouchV2 *multi_touch_v2 = (TF_MultiTouchV2 *)device;
    TF_HALCommon *hal_common = tf_hal_get_common(multi_touch_v2->tfp->spitfp->hal);
    (void)payload;

    switch (fid) {
        case TF_MULTI_TOUCH_V2_CALLBACK_TOUCH_STATE: {
            TF_MultiTouchV2_TouchStateHandler fn = multi_touch_v2->touch_state_handler;
            void *user_data = multi_touch_v2->touch_state_user_data;
            if (fn == NULL) {
                return false;
            }

            bool state[13]; tf_packet_buffer_read_bool_array(payload, state, 13);
            hal_common->locked = true;
            fn(multi_touch_v2, state, user_data);
            hal_common->locked = false;
            break;
        }

        default:
            return false;
    }

    return true;
}
#else
static bool tf_multi_touch_v2_callback_handler(void *device, uint8_t fid, TF_PacketBuffer *payload) {
    return false;
}
#endif
int tf_multi_touch_v2_create(TF_MultiTouchV2 *multi_touch_v2, const char *uid_or_port_name, TF_HAL *hal) {
    if (multi_touch_v2 == NULL || hal == NULL) {
        return TF_E_NULL;
    }

    memset(multi_touch_v2, 0, sizeof(TF_MultiTouchV2));

    TF_TFP *tfp;
    int rc = tf_hal_get_attachable_tfp(hal, &tfp, uid_or_port_name, TF_MULTI_TOUCH_V2_DEVICE_IDENTIFIER);

    if (rc != TF_E_OK) {
        return rc;
    }

    multi_touch_v2->tfp = tfp;
    multi_touch_v2->tfp->device = multi_touch_v2;
    multi_touch_v2->tfp->cb_handler = tf_multi_touch_v2_callback_handler;
    multi_touch_v2->magic = 0x5446;
    multi_touch_v2->response_expected[0] = 0x01;
    multi_touch_v2->response_expected[1] = 0x00;
    return TF_E_OK;
}

int tf_multi_touch_v2_destroy(TF_MultiTouchV2 *multi_touch_v2) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }
    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    multi_touch_v2->tfp->cb_handler = NULL;
    multi_touch_v2->tfp->device = NULL;
    multi_touch_v2->tfp = NULL;
    multi_touch_v2->magic = 0;

    return TF_E_OK;
}

int tf_multi_touch_v2_get_response_expected(TF_MultiTouchV2 *multi_touch_v2, uint8_t function_id, bool *ret_response_expected) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    switch (function_id) {
        case TF_MULTI_TOUCH_V2_FUNCTION_SET_TOUCH_STATE_CALLBACK_CONFIGURATION:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (multi_touch_v2->response_expected[0] & (1 << 0)) != 0;
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_RECALIBRATE:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (multi_touch_v2->response_expected[0] & (1 << 1)) != 0;
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_SET_ELECTRODE_CONFIG:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (multi_touch_v2->response_expected[0] & (1 << 2)) != 0;
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_SET_ELECTRODE_SENSITIVITY:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (multi_touch_v2->response_expected[0] & (1 << 3)) != 0;
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_SET_TOUCH_LED_CONFIG:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (multi_touch_v2->response_expected[0] & (1 << 4)) != 0;
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (multi_touch_v2->response_expected[0] & (1 << 5)) != 0;
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_SET_STATUS_LED_CONFIG:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (multi_touch_v2->response_expected[0] & (1 << 6)) != 0;
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_RESET:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (multi_touch_v2->response_expected[0] & (1 << 7)) != 0;
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_WRITE_UID:
            if (ret_response_expected != NULL) {
                *ret_response_expected = (multi_touch_v2->response_expected[1] & (1 << 0)) != 0;
            }
            break;
        default:
            return TF_E_INVALID_PARAMETER;
    }

    return TF_E_OK;
}

int tf_multi_touch_v2_set_response_expected(TF_MultiTouchV2 *multi_touch_v2, uint8_t function_id, bool response_expected) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    switch (function_id) {
        case TF_MULTI_TOUCH_V2_FUNCTION_SET_TOUCH_STATE_CALLBACK_CONFIGURATION:
            if (response_expected) {
                multi_touch_v2->response_expected[0] |= (1 << 0);
            } else {
                multi_touch_v2->response_expected[0] &= ~(1 << 0);
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_RECALIBRATE:
            if (response_expected) {
                multi_touch_v2->response_expected[0] |= (1 << 1);
            } else {
                multi_touch_v2->response_expected[0] &= ~(1 << 1);
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_SET_ELECTRODE_CONFIG:
            if (response_expected) {
                multi_touch_v2->response_expected[0] |= (1 << 2);
            } else {
                multi_touch_v2->response_expected[0] &= ~(1 << 2);
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_SET_ELECTRODE_SENSITIVITY:
            if (response_expected) {
                multi_touch_v2->response_expected[0] |= (1 << 3);
            } else {
                multi_touch_v2->response_expected[0] &= ~(1 << 3);
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_SET_TOUCH_LED_CONFIG:
            if (response_expected) {
                multi_touch_v2->response_expected[0] |= (1 << 4);
            } else {
                multi_touch_v2->response_expected[0] &= ~(1 << 4);
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER:
            if (response_expected) {
                multi_touch_v2->response_expected[0] |= (1 << 5);
            } else {
                multi_touch_v2->response_expected[0] &= ~(1 << 5);
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_SET_STATUS_LED_CONFIG:
            if (response_expected) {
                multi_touch_v2->response_expected[0] |= (1 << 6);
            } else {
                multi_touch_v2->response_expected[0] &= ~(1 << 6);
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_RESET:
            if (response_expected) {
                multi_touch_v2->response_expected[0] |= (1 << 7);
            } else {
                multi_touch_v2->response_expected[0] &= ~(1 << 7);
            }
            break;
        case TF_MULTI_TOUCH_V2_FUNCTION_WRITE_UID:
            if (response_expected) {
                multi_touch_v2->response_expected[1] |= (1 << 0);
            } else {
                multi_touch_v2->response_expected[1] &= ~(1 << 0);
            }
            break;
        default:
            return TF_E_INVALID_PARAMETER;
    }

    return TF_E_OK;
}

int tf_multi_touch_v2_set_response_expected_all(TF_MultiTouchV2 *multi_touch_v2, bool response_expected) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    memset(multi_touch_v2->response_expected, response_expected ? 0xFF : 0, 2);

    return TF_E_OK;
}

int tf_multi_touch_v2_get_touch_state(TF_MultiTouchV2 *multi_touch_v2, bool ret_state[13]) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_GET_TOUCH_STATE, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(multi_touch_v2->tfp);
        if (_error_code != 0 || _length != 2) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_state != NULL) { tf_packet_buffer_read_bool_array(_recv_buf, ret_state, 13);} else { tf_packet_buffer_remove(_recv_buf, 2); }
        }
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 2) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_set_touch_state_callback_configuration(TF_MultiTouchV2 *multi_touch_v2, uint32_t period, bool value_has_to_change) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_multi_touch_v2_get_response_expected(multi_touch_v2, TF_MULTI_TOUCH_V2_FUNCTION_SET_TOUCH_STATE_CALLBACK_CONFIGURATION, &_response_expected);
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_SET_TOUCH_STATE_CALLBACK_CONFIGURATION, 5, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(multi_touch_v2->tfp);

    period = tf_leconvert_uint32_to(period); memcpy(_send_buf + 0, &period, 4);
    _send_buf[4] = value_has_to_change ? 1 : 0;

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_get_touch_state_callback_configuration(TF_MultiTouchV2 *multi_touch_v2, uint32_t *ret_period, bool *ret_value_has_to_change) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_GET_TOUCH_STATE_CALLBACK_CONFIGURATION, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(multi_touch_v2->tfp);
        if (_error_code != 0 || _length != 5) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_period != NULL) { *ret_period = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
            if (ret_value_has_to_change != NULL) { *ret_value_has_to_change = tf_packet_buffer_read_bool(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
        }
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 5) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_recalibrate(TF_MultiTouchV2 *multi_touch_v2) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_multi_touch_v2_get_response_expected(multi_touch_v2, TF_MULTI_TOUCH_V2_FUNCTION_RECALIBRATE, &_response_expected);
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_RECALIBRATE, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_set_electrode_config(TF_MultiTouchV2 *multi_touch_v2, const bool enabled_electrodes[13]) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_multi_touch_v2_get_response_expected(multi_touch_v2, TF_MULTI_TOUCH_V2_FUNCTION_SET_ELECTRODE_CONFIG, &_response_expected);
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_SET_ELECTRODE_CONFIG, 2, _response_expected);

    size_t _i;
    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(multi_touch_v2->tfp);

    memset(_send_buf + 0, 0, 2); for (_i = 0; _i < 13; ++_i) _send_buf[0 + (_i / 8)] |= (enabled_electrodes[_i] ? 1 : 0) << (_i % 8);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_get_electrode_config(TF_MultiTouchV2 *multi_touch_v2, bool ret_enabled_electrodes[13]) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_GET_ELECTRODE_CONFIG, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(multi_touch_v2->tfp);
        if (_error_code != 0 || _length != 2) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_enabled_electrodes != NULL) { tf_packet_buffer_read_bool_array(_recv_buf, ret_enabled_electrodes, 13);} else { tf_packet_buffer_remove(_recv_buf, 2); }
        }
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 2) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_set_electrode_sensitivity(TF_MultiTouchV2 *multi_touch_v2, uint8_t sensitivity) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_multi_touch_v2_get_response_expected(multi_touch_v2, TF_MULTI_TOUCH_V2_FUNCTION_SET_ELECTRODE_SENSITIVITY, &_response_expected);
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_SET_ELECTRODE_SENSITIVITY, 1, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(multi_touch_v2->tfp);

    _send_buf[0] = (uint8_t)sensitivity;

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_get_electrode_sensitivity(TF_MultiTouchV2 *multi_touch_v2, uint8_t *ret_sensitivity) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_GET_ELECTRODE_SENSITIVITY, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(multi_touch_v2->tfp);
        if (_error_code != 0 || _length != 1) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_sensitivity != NULL) { *ret_sensitivity = tf_packet_buffer_read_uint8_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
        }
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 1) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_set_touch_led_config(TF_MultiTouchV2 *multi_touch_v2, uint8_t config) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_multi_touch_v2_get_response_expected(multi_touch_v2, TF_MULTI_TOUCH_V2_FUNCTION_SET_TOUCH_LED_CONFIG, &_response_expected);
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_SET_TOUCH_LED_CONFIG, 1, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(multi_touch_v2->tfp);

    _send_buf[0] = (uint8_t)config;

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_get_touch_led_config(TF_MultiTouchV2 *multi_touch_v2, uint8_t *ret_config) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_GET_TOUCH_LED_CONFIG, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(multi_touch_v2->tfp);
        if (_error_code != 0 || _length != 1) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_config != NULL) { *ret_config = tf_packet_buffer_read_uint8_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
        }
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 1) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_get_spitfp_error_count(TF_MultiTouchV2 *multi_touch_v2, uint32_t *ret_error_count_ack_checksum, uint32_t *ret_error_count_message_checksum, uint32_t *ret_error_count_frame, uint32_t *ret_error_count_overflow) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_GET_SPITFP_ERROR_COUNT, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(multi_touch_v2->tfp);
        if (_error_code != 0 || _length != 16) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_error_count_ack_checksum != NULL) { *ret_error_count_ack_checksum = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
            if (ret_error_count_message_checksum != NULL) { *ret_error_count_message_checksum = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
            if (ret_error_count_frame != NULL) { *ret_error_count_frame = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
            if (ret_error_count_overflow != NULL) { *ret_error_count_overflow = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
        }
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 16) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_set_bootloader_mode(TF_MultiTouchV2 *multi_touch_v2, uint8_t mode, uint8_t *ret_status) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_SET_BOOTLOADER_MODE, 1, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(multi_touch_v2->tfp);

    _send_buf[0] = (uint8_t)mode;

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(multi_touch_v2->tfp);
        if (_error_code != 0 || _length != 1) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_status != NULL) { *ret_status = tf_packet_buffer_read_uint8_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
        }
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 1) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_get_bootloader_mode(TF_MultiTouchV2 *multi_touch_v2, uint8_t *ret_mode) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_GET_BOOTLOADER_MODE, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(multi_touch_v2->tfp);
        if (_error_code != 0 || _length != 1) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_mode != NULL) { *ret_mode = tf_packet_buffer_read_uint8_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
        }
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 1) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_set_write_firmware_pointer(TF_MultiTouchV2 *multi_touch_v2, uint32_t pointer) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_multi_touch_v2_get_response_expected(multi_touch_v2, TF_MULTI_TOUCH_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, &_response_expected);
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_SET_WRITE_FIRMWARE_POINTER, 4, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(multi_touch_v2->tfp);

    pointer = tf_leconvert_uint32_to(pointer); memcpy(_send_buf + 0, &pointer, 4);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_write_firmware(TF_MultiTouchV2 *multi_touch_v2, const uint8_t data[64], uint8_t *ret_status) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_WRITE_FIRMWARE, 64, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(multi_touch_v2->tfp);

    memcpy(_send_buf + 0, data, 64);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(multi_touch_v2->tfp);
        if (_error_code != 0 || _length != 1) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_status != NULL) { *ret_status = tf_packet_buffer_read_uint8_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
        }
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 1) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_set_status_led_config(TF_MultiTouchV2 *multi_touch_v2, uint8_t config) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_multi_touch_v2_get_response_expected(multi_touch_v2, TF_MULTI_TOUCH_V2_FUNCTION_SET_STATUS_LED_CONFIG, &_response_expected);
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_SET_STATUS_LED_CONFIG, 1, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(multi_touch_v2->tfp);

    _send_buf[0] = (uint8_t)config;

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_get_status_led_config(TF_MultiTouchV2 *multi_touch_v2, uint8_t *ret_config) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_GET_STATUS_LED_CONFIG, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(multi_touch_v2->tfp);
        if (_error_code != 0 || _length != 1) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_config != NULL) { *ret_config = tf_packet_buffer_read_uint8_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 1); }
        }
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 1) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_get_chip_temperature(TF_MultiTouchV2 *multi_touch_v2, int16_t *ret_temperature) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_GET_CHIP_TEMPERATURE, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(multi_touch_v2->tfp);
        if (_error_code != 0 || _length != 2) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_temperature != NULL) { *ret_temperature = tf_packet_buffer_read_int16_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 2); }
        }
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 2) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_reset(TF_MultiTouchV2 *multi_touch_v2) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_multi_touch_v2_get_response_expected(multi_touch_v2, TF_MULTI_TOUCH_V2_FUNCTION_RESET, &_response_expected);
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_RESET, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_write_uid(TF_MultiTouchV2 *multi_touch_v2, uint32_t uid) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_multi_touch_v2_get_response_expected(multi_touch_v2, TF_MULTI_TOUCH_V2_FUNCTION_WRITE_UID, &_response_expected);
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_WRITE_UID, 4, _response_expected);

    uint8_t *_send_buf = tf_tfp_get_send_payload_buffer(multi_touch_v2->tfp);

    uid = tf_leconvert_uint32_to(uid); memcpy(_send_buf + 0, &uid, 4);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 0) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_read_uid(TF_MultiTouchV2 *multi_touch_v2, uint32_t *ret_uid) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_READ_UID, 0, _response_expected);

    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(multi_touch_v2->tfp);
        if (_error_code != 0 || _length != 4) {
            tf_packet_buffer_remove(_recv_buf, _length);
        } else {
            if (ret_uid != NULL) { *ret_uid = tf_packet_buffer_read_uint32_t(_recv_buf); } else { tf_packet_buffer_remove(_recv_buf, 4); }
        }
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 4) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}

int tf_multi_touch_v2_get_identity(TF_MultiTouchV2 *multi_touch_v2, char ret_uid[8], char ret_connected_uid[8], char *ret_position, uint8_t ret_hardware_version[3], uint8_t ret_firmware_version[3], uint16_t *ret_device_identifier) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *_hal = multi_touch_v2->tfp->spitfp->hal;

    if (tf_hal_get_common(_hal)->locked) {
        return TF_E_LOCKED;
    }

    bool _response_expected = true;
    tf_tfp_prepare_send(multi_touch_v2->tfp, TF_MULTI_TOUCH_V2_FUNCTION_GET_IDENTITY, 0, _response_expected);

    size_t _i;
    uint32_t _deadline = tf_hal_current_time_us(_hal) + tf_hal_get_common(_hal)->timeout;

    uint8_t _error_code = 0;
    uint8_t _length = 0;
    int _result = tf_tfp_send_packet(multi_touch_v2->tfp, _response_expected, _deadline, &_error_code, &_length, TF_NEW_PACKET);

    if (_result < 0) {
        return _result;
    }


    if (_result & TF_TICK_PACKET_RECEIVED) {
        TF_PacketBuffer *_recv_buf = tf_tfp_get_receive_buffer(multi_touch_v2->tfp);
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
        tf_tfp_packet_processed(multi_touch_v2->tfp);
    }


    if (_result & TF_TICK_TIMEOUT) {
        _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);
        (void) _result;
        return TF_E_TIMEOUT;
    }

    _result = tf_tfp_finish_send(multi_touch_v2->tfp, _result, _deadline);

    if (_error_code == 0 && _length != 25) {
        return TF_E_WRONG_RESPONSE_LENGTH;
    }

    if (_result < 0) {
        return _result;
    }

    return tf_tfp_get_error(_error_code);
}
#if TF_IMPLEMENT_CALLBACKS != 0
int tf_multi_touch_v2_register_touch_state_callback(TF_MultiTouchV2 *multi_touch_v2, TF_MultiTouchV2_TouchStateHandler handler, void *user_data) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    multi_touch_v2->touch_state_handler = handler;
    multi_touch_v2->touch_state_user_data = user_data;

    return TF_E_OK;
}
#endif
int tf_multi_touch_v2_callback_tick(TF_MultiTouchV2 *multi_touch_v2, uint32_t timeout_us) {
    if (multi_touch_v2 == NULL) {
        return TF_E_NULL;
    }

    if (multi_touch_v2->magic != 0x5446 || multi_touch_v2->tfp == NULL) {
        return TF_E_NOT_INITIALIZED;
    }

    TF_HAL *hal = multi_touch_v2->tfp->spitfp->hal;

    return tf_tfp_callback_tick(multi_touch_v2->tfp, tf_hal_current_time_us(hal) + timeout_us);
}

#ifdef __cplusplus
}
#endif
