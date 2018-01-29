#pragma once

#ifdef WIN32
    #ifdef JAGERTS_FELCP_IO_DLL
        #define JAGERTS_FELCP_IO_API __declspec(dllexport)
    #else
        #define JAGERTS_FELCP_IO_API __declspec(dllimport)
    #endif

    #ifdef JAGERTS_FELCP_XML_DLL
        #define JAGERTS_FELCP_XML_API __declspec(dllexport)
    #else
        #define JAGERTS_FELCP_XML_API __declspec(dllimport)
    #endif

    #ifdef JAGERTS_FELCP_IO_XML_DLL
        #define JAGERTS_FELCP_IO_XML_API __declspec(dllexport)
    #else
        #define JAGERTS_FELCP_IO_XML_API __declspec(dllimport)
    #endif

    #ifdef JAGERTS_FELCP_HELPERS_DLL
        #define JAGERTS_FELCP_HELPERS_API __declspec(dllexport)
    #else
        #define JAGERTS_FELCP_HELPERS_API __declspec(dllimport)
    #endif

    #ifdef JAGERTS_FELCP_IMAGING_DLL
        #define JAGERTS_FELCP_IMAGING_API __declspec(dllexport)
    #else
        #define JAGERTS_FELCP_IMAGING_API __declspec(dllimport)
    #endif

    #ifdef JAGERTS_FELCP_IO_IMAGING_DLL
        #define JAGERTS_FELCP_IO_IMAGING_API __declspec(dllexport)
    #else
        #define JAGERTS_FELCP_IO_IMAGING_API __declspec(dllimport)
    #endif
#else
    #define JAGERTS_FELCP_IO_API
    #define JAGERTS_FELCP_XML_API
    #define JAGERTS_FELCP_IO_XML_API
    #define JAGERTS_FELCP_HELPERS_API
    #define JAGERTS_FELCP_IMAGING_API
    #define JAGERTS_FELCP_IO_IMAGING_API
#endif