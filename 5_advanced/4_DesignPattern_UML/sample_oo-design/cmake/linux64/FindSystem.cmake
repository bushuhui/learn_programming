set(SYSTEM_FOUND 1)

IF(WIN32)
    set(SYSTEM_LIBRARIES pthread Iphlpapi wsock32 Ws2_32 Vfw32 Winmm Comctl32)
ELSE(WIN32)
    set(SYSTEM_LIBRARIES pthread dl X11)
    
    if(TCMALLOC_ENABLED)
        set(SYSTEM_LIBRARIES pthread dl tcmalloc)
    endif()

    # for static Qt
    #set(SYSTEM_LIBRARIES ${SYSTEM_LIBRARIES} z m gthread-2.0 glib-2.0 rt freetype gobject-2.0 glib-2.0 SM ICE Xrender fontconfig freetype Xext X11 )
ENDIF(WIN32)
