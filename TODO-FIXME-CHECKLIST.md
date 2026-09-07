# Checklist TODO și FIXME

Inventar textual al worktree-ului Graphix/SDL, generat la 2026-09-07. Nu este un plan de implementare și nu confirmă că fiecare marcaj reprezintă o problemă încă actuală.

- **703** linii potrivite în **258** fișiere.
- **201** linii conțin TODO; **502** linii conțin FIXME. O linie poate conține ambele.
- Fiecare linie potrivită are un singur element nebifat, cu numărul liniei și textul original. Sunt incluse codul terț, documentația, configurația și identificatorii precum `todo`, fără filtrare semantică.
- Căutarea nu diferențiază majusculele de minuscule și caută cuvinte întregi. Respectă regulile ignore ale `rg`; fișierele ascunse, ignorate și binare nu sunt incluse. Acest raport se exclude pe sine.
- Numerele liniilor reprezintă acest snapshot și se pot schimba ulterior. Comentariile multilinie sunt reprezentate prin liniile care conțin efectiv marcajul.

Comanda de inventariere:

```powershell
rg --json -i '\b(?:TODO|FIXME)\b' --glob '!TODO-FIXME-CHECKLIST.md'
```

## `android-project/app/src/main/java/org/libsdl/app/HIDDeviceBLESteamController.java`

- [ ] Linia **432**: `             boolean result = op.finish(); // TODO: Maybe in main thread as well? `

## `android-project/app/src/main/java/org/libsdl/app/SDLActivity.java`

- [ ] Linia **774**: `             // TODO: Detect the file MIME type and pass the filter value accordingly. `
- [ ] Linia **862**: `                     // FIXME: Why aren't we enabling sensor input at start? `
- [ ] Linia **1640**: `         // TODO set values from "flags" to messagebox dialog `
- [ ] Linia **1723**: `                 // TODO set color for border of messagebox button `
- [ ] Linia **1736**: `                 // TODO set color for selected messagebox button `

## `android-project/app/src/main/java/org/libsdl/app/SDLDummyEdit.java`

- [ ] Linia **42**: `         // FIXME: Discussion at http://bugzilla.libsdl.org/show_bug.cgi?id=1639 `
- [ ] Linia **43**: `         // FIXME: This is not a 100% effective solution to the problem of detecting if the keyboard is showing or not `
- [ ] Linia **44**: `         // FIXME: A more effective solution would be to assume our Layout to be RelativeLayout or LinearLayout `
- [ ] Linia **45**: `         // FIXME: And determine the keyboard presence doing this: http://stackoverflow.com/questions/2150078/how-to-check-visibility-of-software-keyboard-in-android `
- [ ] Linia **46**: `         // FIXME: An even more effective way would be if Android provided this out of the box, but where would the fun be in that :) `

## `android-project/app/src/main/java/org/libsdl/app/SDLInputConnection.java`

- [ ] Linia **103**: `         /* FIXME: This doesn't handle graphemes, like '🌬️' */ `

## `android-project/app/src/main/java/org/libsdl/app/SDLSurface.java`

- [ ] Linia **329**: `         // TODO: This uses getDefaultSensor - what if we have >1 accels? `
- [ ] Linia **342**: `         // TODO `

## `build-scripts/build-release.py`

- [ ] Linia **528**: `         # FIXME: find out why some files are not shown in "git log" `

## `build-scripts/build-web-examples.pl`

- [ ] Linia **398**: `     # !!! FIXME: this needs to generate a preview page for all the categories. `

## `build-scripts/makecasefoldhashtable.pl`

- [ ] Linia **181**: `             die("Uhoh, a codepoint > 0xFFFF that folds to multiple codepoints! Fixme.") if defined($map2); `

## `build-scripts/SDL_migration.cocci`

- [ ] Linia **42**: ` + /* FIXME MIGRATION: maybe move this to a global scope ? */ `
- [ ] Linia **154**: ` + /* FIXME MIGRATION: check for valid instance */ `
- [ ] Linia **161**: ` + /* FIXME MIGRATION: check for valid instance */ `
- [ ] Linia **168**: ` + /* FIXME MIGRATION: check for valid instance */ `
- [ ] Linia **175**: ` + /* FIXME MIGRATION: check for valid instance */ `
- [ ] Linia **182**: ` + /* FIXME MIGRATION: check for valid instance */ `
- [ ] Linia **189**: ` + /* FIXME MIGRATION: check for valid instance */ `
- [ ] Linia **196**: ` + /* FIXME MIGRATION: check for valid instance */ `
- [ ] Linia **203**: ` + /* FIXME MIGRATION: check for valid instance */ `
- [ ] Linia **210**: ` + /* FIXME MIGRATION: SDL_Has3DNow() has been removed; there is no replacement. */ 0 `
- [ ] Linia **216**: ` + /* FIXME MIGRATION: SDL_HasRDTSC() has been removed; there is no replacement. */ 0 `
- [ ] Linia **222**: ` + /* FIXME MIGRATION: no longer support by the X11 backend */ NULL `
- [ ] Linia **228**: ` + /* FIXME MIGRATION: no longer support by the X11 backend */ NULL `
- [ ] Linia **250**: ` + /* FIXME MIGRATION: SDL_GetRevisionNumber() removed */ 0 `
- [ ] Linia **268**: ` +  /* FIXME MIGRATION: double-check if you use the returned value of SDL_RWread() */ `
- [ ] Linia **290**: ` +  /* FIXME MIGRATION: double-check if you use the returned value of SDL_RWwrite() */ `
- [ ] Linia **2146**: ` + /* FIXME MIGRATION: SDL_WINDOWEVENT_TAKE_FOCUS has been removed; there is no replacement. */ 0 `

## `build-scripts/update-version.sh`

- [ ] Linia **32**: ` # !!! FIXME: This first one is a kinda scary search/replace that might fail later if another X.Y.Z version is added to the file. `

## `build-scripts/wikiheaders.pl`

- [ ] Linia **249**: `         $retval = "$p\n";  # don't wrap it (!!! FIXME: but maybe parse by lines until we run out of table...) `
- [ ] Linia **759**: `     if (0) {  # !!! FIXME: this lists things that _shouldn't_ be in the headers, like MigrationGuide, etc, but also we don't know if they're functions, macros, etc at this point (can we parse that from the wiki page, though?) `
- [ ] Linia **777**: ` # !!! FIXME: generalize this for other libraries to use. `
- [ ] Linia **893**: `     # !!! FIXME: this gitrev and majorver/etc stuff is copy/pasted a few times now. `
- [ ] Linia **899**: `     # !!! FIXME `
- [ ] Linia **1426**: `             # !!! FIXME: code duplication with typedef processing, below. `
- [ ] Linia **1827**: `             die("Unexpected wiki file type. Fixme!"); `
- [ ] Linia **1961**: `             # !!! FIXME: lots of code duplication in all of these. `
- [ ] Linia **2071**: `             # !!! FIXME: lots of code duplication in all of these. `
- [ ] Linia **2086**: `             # !!! FIXME: lots of code duplication in all of these. `
- [ ] Linia **2101**: `             # !!! FIXME: lots of code duplication in all of these. `
- [ ] Linia **2317**: `                 # !!! FIXME: complain if this isn't a function or macro. `
- [ ] Linia **2351**: `                 } elsif (($symtype != 1) && ($symtype != 2) && ($symtype != 5)) {  # !!! FIXME: if 5, make sure it's a function pointer typedef! `
- [ ] Linia **2421**: `         # !!! FIXME: uncomment this when we're trying to clean this up in the headers. `
- [ ] Linia **2462**: `         if (0) {  # !!! FIXME: this was a useful hack, but this needs to be generalized if we're going to do this always. `
- [ ] Linia **2849**: `     # !!! FIXME `
- [ ] Linia **2949**: `         $str .= ".\\\"   https://github.com/libsdl-org/SDL/issues/new?title=Misgenerated%20manpage%20for%20$sym\n";  # !!! FIXME: if this becomes a problem for other projects, we'll generalize this. `
- [ ] Linia **3104**: `             # !!! FIXME: lots of code duplication in all of these. `
- [ ] Linia **3169**: `     # !!! FIXME: code duplication with --copy-to-manpages section. `
- [ ] Linia **3186**: `     # !!! FIXME `
- [ ] Linia **3250**: `     # !!! FIXME: Maybe put this in the book intro?  print TEXFH $introtxt; `
- [ ] Linia **3355**: `             # !!! FIXME: this table parsing has gotten complicated and is pasted three times in this file; move it to a subroutine! `
- [ ] Linia **3440**: `             # !!! FIXME: lots of code duplication in all of these. `
- [ ] Linia **3463**: `         # !!! FIXME: Maybe put copyright in the book intro? `

## `cmake/CPackProjectConfig.cmake.in`

- [ ] Linia **34**: `     # FIXME: use pre-built/create .DS_Store through AppleScript (CPACK_DMG_DS_STORE/CPACK_DMG_DS_STORE_SETUP_SCRIPT) `

## `cmake/GetGitRevisionDescription.cmake`

- [ ] Linia **209**: `     # TODO sanitize `

## `cmake/macros.cmake`

- [ ] Linia **452**: `     # FIXME: Use $<TARGET_COMPILE_PDB_FILE:${TARGET} once it becomes available (https://gitlab.kitware.com/cmake/cmake/-/issues/25244) `

## `cmake/sdlchecks.cmake`

- [ ] Linia **16**: `   # FIXME: fail FindLibraryAndSONAME when library is not shared. `
- [ ] Linia **124**: `         #FIXME: remove this line and property generate sdl3.pc `
- [ ] Linia **800**: `       # FIXME: Use Find module `
- [ ] Linia **1240**: `     #FIXME: properly add usb libs with pkg-config or whatever `

## `cmake/sdlmanpages.cmake`

- [ ] Linia **25**: `   # FIXME: get rid of SYMBOL and let the perl script figure out the dependencies `

## `cmake/test/CMakeLists.txt`

- [ ] Linia **8**: ` # FIXME: how to target ios/tvos with Swift? `

## `CMakeLists.txt`

- [ ] Linia **575**: `     # FIXME `
- [ ] Linia **669**: `     #FIXME: originally this if had an additional "AND NOT (USE_CLANG AND WINDOWS)" `
- [ ] Linia **910**: `     # TODO: Those all seem to be quite GCC specific - needs to be `
- [ ] Linia **1042**: ` # TODO: Can't deactivate on FreeBSD? w/o LIBC, SDL_stdinc.h can't define anything. `
- [ ] Linia **1366**: `   # !!! FIXME: for later. `
- [ ] Linia **1469**: `   set(SDL_FSOPS_POSIX 1)  # !!! FIXME: this might need something else for .apk data? `
- [ ] Linia **1557**: `     # FIXME failing dlopen https://github.com/android-ndk/ndk/issues/929 `
- [ ] Linia **2232**: `     if(SDL_CPU_ARM32)  # !!! FIXME: this should probably check if we're !(x86 or x86-64) instead of arm. `
- [ ] Linia **2494**: `   # TODO: rework this all for proper macOS, iOS and Darwin support `
- [ ] Linia **2496**: ``   # !!! FIXME: all the `if(IOS OR TVOS OR VISIONOS)` checks should get merged into one variable, so we're ready for the next platform (or just WatchOS). ``
- [ ] Linia **2499**: `   # !!! FIXME: we need Carbon for some very old API calls in `
- [ ] Linia **2500**: `   # !!! FIXME:  src/video/cocoa/SDL_cocoakeyboard.c, but we should figure out `
- [ ] Linia **2501**: `   # !!! FIXME:  how to dump those. `
- [ ] Linia **2645**: `   # TODO: SDL_STORAGE_ICLOUD `
- [ ] Linia **2859**: `       # TODO: Use FIND_PACKAGE(OpenGL) instead `
- [ ] Linia **3276**: `   # !!! FIXME: do we need a FSops implementation for this? `
- [ ] Linia **4092**: `   # FIXME: get rid of EXTRA_TEST_LIBS variable `

## `docs/doxyfile`

- [ ] Linia **437**: ` # disable (NO) the todo list. This list is created by putting \todo  `

## `docs/README-ios.md`

- [ ] Linia **78**: ` TODO: Add information regarding App Store requirements such as icons, etc. `

## `docs/README-migration.md`

- [ ] Linia **51**: ` Some macros are renamed and/or removed in SDL3. We have provided a handy Python script [rename_macros.py](https://github.com/libsdl-org/SDL/blob/main/build-scripts/rename_macros.py) to replace these, and also add fixme comments on how to further improve the code: `

## `examples/template.html`

- [ ] Linia **281**: `         // TODO: do not warn on ok events like simulating an infinite loop or exitStatus `

## `include/build_config/SDL_build_config_wingdk.h`

- [ ] Linia **229**: ` /* Enable the camera driver (src/camera/dummy/\*.c) */  /* !!! FIXME */ `

## `include/build_config/SDL_build_config_xbox.h`

- [ ] Linia **212**: ` /* Disable IME as not supported yet (TODO: Xbox IME?) */ `

## `include/build_config/SDL_build_config.h.cmake`

- [ ] Linia **538**: ` /* !!! FIXME: for later cmakedefine SDL_CAMERA_DRIVER_DISK 1 */ `

## `include/SDL3/SDL_begin_code.h`

- [ ] Linia **511**: ` /** FIXME `

## `include/SDL3/SDL_gpu.h`

- [ ] Linia **682**: `  * FIXME: Check universal support for 32-bit component formats FIXME: Check `

## `include/SDL3/SDL_haptic.h`

- [ ] Linia **130**: ` /* FIXME: `

## `include/SDL3/SDL_stdinc.h`

- [ ] Linia **1201**: ` /* TODO: include/SDL_stdinc.h:390: error: size of array 'SDL_dummy_enum' is negative */ `

## `src/atomic/SDL_atomic.c`

- [ ] Linia **28**: ` #ifdef SDL_PLATFORM_MACOS // !!! FIXME: should we favor gcc atomics? `

## `src/atomic/SDL_spinlock.c`

- [ ] Linia **153**: `     // FIXME: Should we have an eventual timeout? `
- [ ] Linia **159**: `             // !!! FIXME: this doesn't definitely give up the current timeslice, it does different things on various platforms. `

## `src/audio/aaudio/SDL_aaudio.c`

- [ ] Linia **273**: `             // !!! FIXME: do we have to wait for the state to change to make sure all buffered audio has played, or will close do this (or will the system do this after the close)? `
- [ ] Linia **274**: `             // !!! FIXME: also, will this definitely wait for a running data callback to finish, and then stop the callback from firing again? `
- [ ] Linia **301**: `             // !!! FIXME: I _think_ this is okay with the current set of usages we support, but the docs `
- [ ] Linia **302**: `             // !!! FIXME:  say you need to dip down into Java to call android.app.Activity.setVolumeControlStream(usage) `
- [ ] Linia **303**: `             // !!! FIXME:  so the physical volume buttons control this stream, but that might be more for special cases `
- [ ] Linia **304**: `             // !!! FIXME:  like notification sounds, etc, and it's possible you _don't_ want to override this for those `
- [ ] Linia **305**: `             // !!! FIXME:  special cases, too! We'll revisit if there are bug reports. `
- [ ] Linia **446**: ` // !!! FIXME: make this non-blocking! `
- [ ] Linia **461**: `         // !!! FIXME: make this non-blocking! `

## `src/audio/alsa/SDL_alsa_audio.c`

- [ ] Linia **49**: ` //TODO: cleanup once the code settled down `
- [ ] Linia **330**: ` // TODO: Figure out the "right"(TM) way. For the moment we presume that if a system is using a `
- [ ] Linia **363**: `     const int status = ALSA_snd_pcm_recover(pcm, errnum, 0);  // !!! FIXME: third parameter is non-zero to prevent libasound from printing error messages. Should we do that? `
- [ ] Linia **402**: `     Uint8 *sample_buf = (Uint8 *) buffer;  // !!! FIXME: deal with this without casting away constness `

## `src/audio/coreaudio/SDL_coreaudio.m`

- [ ] Linia **846**: `         // !!! FIXME: should we use AudioQueueEnqueueBufferWithParameters and specify all frames be "trimmed" so these are immediately ready to refill with SDL callback data? `

## `src/audio/directsound/SDL_directsound.h`

- [ ] Linia **33**: `     // !!! FIXME: make this a union with capture/playback sections? `

## `src/audio/dsp/SDL_dspaudio.c`

- [ ] Linia **23**: ` // !!! FIXME: clean out perror and fprintf calls in here. `

## `src/audio/haiku/SDL_haikuaudio.cc`

- [ ] Linia **119**: `     format.channel_count = device->spec.channels;        // !!! FIXME: support > 2? `

## `src/audio/jack/SDL_jackaudio.c`

- [ ] Linia **63**: ` // !!! FIXME: this is copy/pasted in several places now `
- [ ] Linia **271**: ` // !!! FIXME: unify this (PulseAudio has a getAppName, Pipewire has a thing, etc) `

## `src/audio/n3ds/SDL_n3dsaudio.c`

- [ ] Linia **188**: `         return true;  // !!! FIXME: is this a fatal error? If so, this should return false. `

## `src/audio/openslES/SDL_openslES.c`

- [ ] Linia **229**: ` // !!! FIXME: make this non-blocking! `
- [ ] Linia **248**: `     // !!! FIXME: make this non-blocking! `

## `src/audio/qnx/SDL_qsa_audio.c`

- [ ] Linia **22**: ` // !!! FIXME: can this target support hotplugging? `
- [ ] Linia **60**: ` // !!! FIXME: does this need to be here? Does the SDL version not work? `
- [ ] Linia **103**: `         device->hidden->timeout_on_wait = true;  // !!! FIXME: Should we just disconnect the device in this case? `
- [ ] Linia **128**: `                     return true;  // oh well, try again next time.  !!! FIXME: Should we just disconnect the device in this case? `
- [ ] Linia **196**: `         return SDL_SetError("SDL recording support isn't available on QNX atm"); // !!! FIXME: most of this code has support for recording devices, but there's no RecordDevice, etc functions. Fill them in! `
- [ ] Linia **356**: `                     #if 0  // !!! FIXME: most of this code has support for recording devices, but there's no RecordDevice, etc functions. Fill them in! `
- [ ] Linia **382**: `                         // !!! FIXME: I'm assuming each of these values are way less than 0xFFFF. Fix this if not. `
- [ ] Linia **407**: `         // !!! FIXME: I'm assuming each of these values are way less than 0xFFFF. Fix this if not. `
- [ ] Linia **416**: `         // !!! FIXME: I'm assuming each of these values are way less than 0xFFFF. Fix this if not. `
- [ ] Linia **440**: `     // !!! FIXME: most of this code has support for recording devices, but there's no RecordDevice, etc functions. Fill them in! `

## `src/audio/SDL_audio.c`

- [ ] Linia **403**: ` static void ReleaseAudioDevice(SDL_AudioDevice *device) SDL_NO_THREAD_SAFETY_ANALYSIS  // !!! FIXME: SDL_RELEASE `
- [ ] Linia **412**: ` static SDL_LogicalAudioDevice *ObtainLogicalAudioDevice(SDL_AudioDeviceID devid, SDL_AudioDevice **_device) SDL_NO_THREAD_SAFETY_ANALYSIS    // !!! FIXME: SDL_ACQUIRE `
- [ ] Linia **466**: ` static SDL_AudioDevice *ObtainPhysicalAudioDevice(SDL_AudioDeviceID devid)  // !!! FIXME: SDL_ACQUIRE `
- [ ] Linia **490**: ` static SDL_AudioDevice *ObtainPhysicalAudioDeviceDefaultAllowed(SDL_AudioDeviceID devid)  // !!! FIXME: SDL_ACQUIRE `
- [ ] Linia **949**: ` // !!! FIXME: the video subsystem does SDL_VideoInit, not SDL_InitVideo. Make this match. `
- [ ] Linia **1288**: `                 // !!! FIXME: we can't promise the device buf is aligned/padded for SIMD. `
- [ ] Linia **1556**: ` // !!! FIXME: SDL convention is for userdata to come first in the callback's params. Fix this at some point. `
- [ ] Linia **2125**: ` // !!! FIXME: this and BindAudioStreams are mutex nightmares.  :/ `
- [ ] Linia **2380**: `     if (!new_default_device) {  // !!! FIXME: what should we do in this case? Maybe all devices are lost, so there _isn't_ a default? `
- [ ] Linia **2405**: `     // !!! FIXME: this duplicates some code we could probably refactor. `
- [ ] Linia **2578**: `         // !!! FIXME: this duplicates some code we could probably refactor. `

## `src/audio/SDL_audiocvt.c`

- [ ] Linia **157**: `     bool has_null_mappings = false;  // !!! FIXME: calculate this when setting the channel map instead. `
- [ ] Linia **186**: `             Uint##bits *tmp = (Uint##bits *) SDL_small_alloc(int, channels, &isstack); /* !!! FIXME: allocate this when setting the channel map instead. */ \ `
- [ ] Linia **969**: `         // !!! FIXME: it would be possible to do this really well in SIMD for stereo data, using unpack (intel) or zip (arm) instructions, etc. `

## `src/audio/SDL_audioqueue.c`

- [ ] Linia **51**: `     int chmap_storage[SDL_MAX_CHANNELMAP_CHANNELS];  // !!! FIXME: this needs to grow if SDL ever supports more channels. But if it grows, we should probably be more clever about allocations. `

## `src/audio/SDL_audioresample.c`

- [ ] Linia **30**: ` // TODO: Support changing this at runtime? `

## `src/audio/SDL_audiotypecvt.c`

- [ ] Linia **488**: ` // FIXME: SDL doesn't have SSSE3 detection, so use the next one up `

## `src/audio/SDL_mixer.c`

- [ ] Linia **85**: ` // !!! FIXME: This needs some SIMD magic. `
- [ ] Linia **86**: ` // !!! FIXME: Add fast-path for volume = 1 `
- [ ] Linia **87**: ` // !!! FIXME: Use larger scales for 16-bit/32-bit integers `
- [ ] Linia **285**: `     default: // If this happens... FIXME! `

## `src/audio/SDL_sysaudio.h`

- [ ] Linia **36**: ` // !!! FIXME: These are wordy and unlocalized... `
- [ ] Linia **49**: ` #define SDL_MAX_CHANNELMAP_CHANNELS 8  // !!! FIXME: if SDL ever supports more channels, clean this out and make those parts dynamic. `
- [ ] Linia **167**: `     bool ProvidesOwnCallbackThread;  // !!! FIXME: rename this, it's not a callback thread anymore. `
- [ ] Linia **170**: `     bool OnlyHasDefaultRecordingDevice;   // !!! FIXME: is there ever a time where you'd have a default playback and not a default recording (or vice versa)? `
- [ ] Linia **195**: `     // !!! FIXME: most (all?) of these don't have to be atomic. `
- [ ] Linia **225**: `     int input_chmap_storage[SDL_MAX_CHANNELMAP_CHANNELS];  // !!! FIXME: this needs to grow if SDL ever supports more channels. But if it grows, we should probably be more clever about allocations. `

## `src/audio/sndio/SDL_sndioaudio.c`

- [ ] Linia **186**: `     // !!! FIXME: this should be non-blocking so we can check device->shutdown. `

## `src/audio/vita/SDL_vitaaudio.c`

- [ ] Linia **140**: `     // !!! FIXME: we might just need to sleep roughly as long as playback buffers take to process, based on sample rate, etc. `

## `src/audio/wasapi/SDL_wasapi.c`

- [ ] Linia **301**: `     ManagementThread = SDL_CreateThreadWithStackSize(ManagementThreadEntry, "SDLWASAPIMgmt", 256 * 1024, &mgmtdata); // !!! FIXME: maybe even smaller stack size? `
- [ ] Linia **675**: `     /* !!! FIXME: we could request an exclusive mode stream, which is lower latency; `

## `src/camera/android/SDL_camera_android.c`

- [ ] Linia **323**: `     // !!! FIXME: this currently copies the data to the surface (see FIXME about non-contiguous planar surfaces, but in theory we could just keep this locked until ReleaseFrame... `
- [ ] Linia **390**: `     // !!! FIXME: this currently copies the data to the surface, but in theory we could just keep the AImage until ReleaseFrame... `
- [ ] Linia **579**: ` #if 0  // !!! FIXME: for now, we'll just let this fail if it is going to fail, without checking for this `
- [ ] Linia **689**: ` #if 0 // !!! FIXME: these all come out with 0 durations on my test phone.  :( `
- [ ] Linia **845**: `     // !!! FIXME: slide this off into a subroutine `

## `src/camera/coremedia/SDL_camera_coremedia.m`

- [ ] Linia **188**: `     // !!! FIXME: this currently copies the data to the surface (see FIXME about non-contiguous planar surfaces, but in theory we could just keep this locked until ReleaseFrame... `
- [ ] Linia **205**: `         // !!! FIXME: we have an open issue in SDL3 to allow SDL_Surface to support non-contiguous planar data, but we don't have it yet. `
- [ ] Linia **269**: `     // !!! FIXME: this currently copies the data to the surface, but in theory we could just keep this locked until ReleaseFrame... `
- [ ] Linia **484**: ``     [session startRunning];  // !!! FIXME: docs say this can block while camera warms up and shouldn't be done on main thread. Maybe push through `queue`? ``
- [ ] Linia **591**: `         // !!! FIXME: this can use Key Value Observation to get hotplug events. `
- [ ] Linia **595**: `         // !!! FIXME: this can use AVCaptureDeviceWasConnectedNotification and AVCaptureDeviceWasDisconnectedNotification with NSNotificationCenter to get hotplug events. `
- [ ] Linia **605**: `     // !!! FIXME: disable hotplug. `

## `src/camera/emscripten/SDL_camera_emscripten.c`

- [ ] Linia **150**: `         function grabNextCameraFrame() {  // !!! FIXME: this (currently) runs as a requestAnimationFrame callback, for lack of a better option. `
- [ ] Linia **168**: `             requestAnimationFrame(grabNextCameraFrame);  // run this function again at the display framerate.  (!!! FIXME: would this be better as requestIdleCallback?) `

## `src/camera/mediafoundation/SDL_camera_mediafoundation.c`

- [ ] Linia **768**: `     // !!! FIXME: I think it'd be nice to do this without an IMFSourceReader, `
- [ ] Linia **776**: `     // !!! FIXME: do we actually have to find the media type object in the source reader or can we just roll our own like this? `
- [ ] Linia **1022**: `     // !!! FIXME: use CM_Register_Notification (Win8+) to get device notifications. `
- [ ] Linia **1023**: `     // !!! FIXME: Earlier versions can use RegisterDeviceNotification, but I'm not bothering: no hotplug for you! `
- [ ] Linia **1077**: `     // !!! FIXME: slide this off into a subroutine `

## `src/camera/SDL_camera.c`

- [ ] Linia **124**: `         // !!! FIXME: this is bad for several reasons (uses double, could be precalculated, doesn't track elapsed time). `
- [ ] Linia **245**: ` // !!! FIXME: the close_cond stuff from audio might help the race condition here. `
- [ ] Linia **314**: ` static void ObtainPhysicalCameraObj(SDL_Camera *device) SDL_NO_THREAD_SAFETY_ANALYSIS  // !!! FIXME: SDL_ACQUIRE `
- [ ] Linia **322**: ` static SDL_Camera *ObtainPhysicalCamera(SDL_CameraID devid)  // !!! FIXME: SDL_ACQUIRE `
- [ ] Linia **341**: ` static void ReleaseCamera(SDL_Camera *device) SDL_NO_THREAD_SAFETY_ANALYSIS  // !!! FIXME: SDL_RELEASE `
- [ ] Linia **642**: `` // !!! FIXME: this doesn't follow SDL convention of `userdata` being the first param of the callback. ``
- [ ] Linia **802**: `     // TODO `
- [ ] Linia **910**: `                 SDL_StretchSurface(srcsurf, NULL, dstsurf, NULL, SDL_SCALEMODE_NEAREST);  // !!! FIXME: linear scale? letterboxing? `
- [ ] Linia **921**: `                 SDL_StretchSurface(srcsurf, NULL, output_surface, NULL, SDL_SCALEMODE_NEAREST);  // !!! FIXME: linear scale? letterboxing? `

## `src/camera/SDL_syscamera.h`

- [ ] Linia **202**: ``     SDL_RWLock *device_hash_lock;  // A rwlock that protects `device_hash`   // !!! FIXME: device_hash _also_ has a rwlock, see if we still need this one. ``

## `src/camera/v4l2/SDL_camera_v4l2.c`

- [ ] Linia **288**: `                 // !!! FIXME: disconnect the device. `
- [ ] Linia **304**: `                 // !!! FIXME: disconnect the device. `
- [ ] Linia **703**: `             // !!! FIXME: should we step by the numerator...? `
- [ ] Linia **717**: `             // FIXME: The current API does not enable exposing continuous ranges, so for now let's expose some common values that are within the range `

## `src/core/android/SDL_android.c`

- [ ] Linia **1495**: `     // TODO: compute new mime types `
- [ ] Linia **1790**: `     *default_playback = *default_recording = NULL;  // !!! FIXME: how do you decide the default device id? `
- [ ] Linia **3060**: `     // !!! FIXME: lots of duplication with SDL_GetAndroidExternalStoragePath and SDL_GetAndroidInternalStoragePath; consolidate these functions! `
- [ ] Linia **3366**: `         // TODO: Fix modified UTF-8 to classic UTF-8 `

## `src/core/haiku/SDL_BApp.h`

- [ ] Linia **66**: `     BAPP_RESTORE, // TODO: IMPLEMENT! `
- [ ] Linia **162**: `             // TODO: Handle screen resize or workspace change `
- [ ] Linia **188**: `         // TODO: error handling `
- [ ] Linia **192**: `     /* FIXME: Bad coding practice, but I can't include SDL_BWin.h here.  Is `

## `src/core/linux/SDL_evdev_capabilities.c`

- [ ] Linia **106**: `             /* TODO: better determining between touchscreen and multitouch touchpad, `

## `src/core/linux/SDL_evdev.c`

- [ ] Linia **79**: `     // TODO: use this for every device, not just touchscreen `
- [ ] Linia **82**: `     /* TODO: expand on this to have data for every possible class (mouse, `
- [ ] Linia **215**: `                 // TODO: Scan the devices manually, like a caveman `
- [ ] Linia **387**: `                         if (!item->is_touchscreen) { // FIXME: temp hack `
- [ ] Linia **393**: `                         if (!item->is_touchscreen) { // FIXME: temp hack `
- [ ] Linia **404**: `                         if (!item->is_touchscreen) { // FIXME: temp hack `
- [ ] Linia **413**: `                         if (!item->is_touchscreen) { // FIXME: temp hack `
- [ ] Linia **422**: `                         if (!item->is_touchscreen) { // FIXME: temp hack `
- [ ] Linia **527**: `                         if (!item->is_touchscreen) { // FIXME: temp hack `
- [ ] Linia **545**: `                             /* FIXME: the touch's window shouldn't be null, but `
- [ ] Linia **794**: `     // TODO: sync devices other than touchscreen `

## `src/core/linux/SDL_fcitx.c`

- [ ] Linia **57**: ` // !!! FIXME: should this just be dumped for src/core/unix's SDL_GetAppID()? `
- [ ] Linia **229**: `         // FIXME, turn off native candidate rendering `

## `src/core/linux/SDL_ibus.c`

- [ ] Linia **418**: `             // FIXME, turn off native candidate rendering `
- [ ] Linia **636**: `     // !!! FIXME: should we close(inotify_fd) here? `

## `src/core/openbsd/SDL_wscons_kbd.c`

- [ ] Linia **585**: `     // FIXME: Get the event time in the SDL tick time base `

## `src/core/openbsd/SDL_wscons_mouse.c`

- [ ] Linia **68**: `     // FIXME: Get the event time in the SDL tick time base `

## `src/core/windows/SDL_hid.c`

- [ ] Linia **244**: `     // FIXME: Should we log errors? `

## `src/core/windows/SDL_immdevice.c`

- [ ] Linia **36**: ` static const ERole SDL_IMMDevice_role = eConsole; // !!! FIXME: should this be eMultimedia? Should be a hint? `
- [ ] Linia **128**: `        available and switch automatically. (!!! FIXME...?) */ `

## `src/core/windows/SDL_windows.h`

- [ ] Linia **134**: ` // !!! FIXME: UTF8ToString() can just be a SDL_strdup() here. `

## `src/cpuinfo/SDL_cpuinfo.c`

- [ ] Linia **727**: ` !!! FIXME: Not used at the moment. */ `

## `src/dialog/unix/SDL_portaldialog.c`

- [ ] Linia **195**: `             signal_data->callback(signal_data->userdata, result_data, -1); // TODO: Set this to the last selected filter `
- [ ] Linia **284**: `         signal_data->callback(signal_data->userdata, path, -1); // TODO: Fetch the index of the filter that was used `
- [ ] Linia **537**: `     /* TODO: This should be registered before opening the portal, or the filter will not catch `

## `src/dialog/unix/SDL_zenitydialog.c`

- [ ] Linia **50**: `        there aren't others. TODO: find something better. */ `
- [ ] Linia **222**: ` // TODO: Zenity survives termination of the parent `

## `src/dialog/windows/SDL_windowsdialog.c`

- [ ] Linia **763**: ` // TODO: The new version of file dialogs `

## `src/dynapi/SDL_dynapi.c`

- [ ] Linia **266**: `     char buf[512]; // !!! FIXME: dynamic allocation `
- [ ] Linia **399**: `         // !!! FIXME: can maybe handle older versions? `

## `src/events/SDL_events.c`

- [ ] Linia **465**: `     // !!! FIXME: This code is kinda ugly, sorry. `
- [ ] Linia **1013**: `        FIXME: Does this introduce any other bugs with events at startup? `

## `src/events/SDL_mouse_c.h`

- [ ] Linia **231**: ` // TODO RECONNECT: Set mouse state to "zero" `

## `src/events/SDL_mouse.c`

- [ ] Linia **550**: ` /* TODO RECONNECT: Hello from the Wayland video driver! `

## `src/events/SDL_touch.c`

- [ ] Linia **360**: `             // FIXME: maybe we should only restrict to a few SDL_TouchDeviceType `

## `src/filesystem/android/SDL_sysfilesystem.c`

- [ ] Linia **58**: `     /* TODO: see https://developer.android.com/reference/android/os/Environment#lfields `

## `src/filesystem/gdk/SDL_sysfilesystem.cpp`

- [ ] Linia **114**: ` // TODO `

## `src/filesystem/haiku/SDL_sysfilesystem.cc`

- [ ] Linia **47**: `     // !!! FIXME: if find_path promises an absolute path, can we dump this and just do SDL_strrchr(name, '/')? `
- [ ] Linia **80**: `     // !!! FIXME: is there a better way to do this? `
- [ ] Linia **128**: `         // TODO: Is Haiku's desktop folder always ~/Desktop/ ? `

## `src/filesystem/n3ds/SDL_sysfilesystem.c`

- [ ] Linia **64**: ` // TODO `

## `src/filesystem/ps2/SDL_sysfilesystem.c`

- [ ] Linia **107**: ` // TODO `

## `src/filesystem/psp/SDL_sysfilesystem.c`

- [ ] Linia **76**: ` // TODO `

## `src/filesystem/riscos/SDL_sysfilesystem.c`

- [ ] Linia **215**: ` // TODO `

## `src/filesystem/SDL_filesystem.c`

- [ ] Linia **314**: ``     // !!! FIXME: if we're careful, we can keep a single buffer in `data` that we push and pop paths off the end of as we walk the tree, ``
- [ ] Linia **315**: `     // !!! FIXME: and only casefold the new pieces instead of allocating and folding full paths for all of this. `
- [ ] Linia **416**: `     // !!! FIXME `

## `src/filesystem/unix/SDL_sysfilesystem.c`

- [ ] Linia **200**: `         /* !!! FIXME: after 2.0.6 ships, let's delete this code and just `

## `src/filesystem/vita/SDL_sysfilesystem.c`

- [ ] Linia **78**: ` // TODO `

## `src/gpu/d3d12/SDL_gpu_d3d12.c`

- [ ] Linia **121**: ` // TODO: do these need to be tuned? `
- [ ] Linia **908**: `     // FIXME: these might not be necessary since we're not using custom heaps `
- [ ] Linia **1109**: `     // todo cleanup `
- [ ] Linia **1244**: ` // FIXME: This is purely to work around a presentation bug when recreating the device/command queue. `
- [ ] Linia **1262**: `     #define MAX_ERROR_LEN 1024 // FIXME: Arbitrary! `
- [ ] Linia **2473**: `     // FIXME: I think the max can be smaller... `
- [ ] Linia **2674**: `     // FIXME: shouldn't have to assert here `
- [ ] Linia **2766**: `     // FIXME: I think the max can be smaller... `
- [ ] Linia **3886**: `         uavDesc.Buffer.CounterOffsetInBytes = 0; // TODO: support counters? `
- [ ] Linia **3893**: `             NULL, // TODO: support counters? `
- [ ] Linia **3922**: `     // FIXME: we may not need a CBV since we use root descriptors `
- [ ] Linia **6656**: `     // FIXME: HDR support would be nice to add, but it seems complicated... `
- [ ] Linia **7694**: `     // FIXME: Should this happen before the inFlightFences stuff above? `
- [ ] Linia **7931**: `     // TODO: More reference counting `
- [ ] Linia **8026**: `         // TODO: compute uniforms `
- [ ] Linia **8112**: `         planeParams.ColorSpace = DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709; // FIXME `
- [ ] Linia **8236**: `                 SET_STRING_ERROR_AND_RETURN("Wait failed", false); // TODO: is there a better way to report this? `
- [ ] Linia **8292**: `         SET_STRING_ERROR_AND_RETURN("Wait failed", false); // TODO: is there a better way to report this? `
- [ ] Linia **8578**: `     // TODO SM7: bool has_spirv = SDL_GetBooleanProperty(props, SDL_PROP_GPU_DEVICE_CREATE_SHADERS_SPIRV_BOOLEAN, false); `
- [ ] Linia **8579**: `     // TODO SM7: bool supports_spirv = false; `

## `src/gpu/metal/SDL_gpu_metal.m`

- [ ] Linia **694**: ` // FIXME: This should be moved into SDL_sysgpu.h `
- [ ] Linia **1373**: `         samplerDesc.mipFilter = SDLToMetal_MipFilter[createinfo->mipmap_mode]; // FIXME: Is this right with non-mipmapped samplers? `
- [ ] Linia **1779**: `         // FIXME: Is this necessary? `
- [ ] Linia **2094**: `     // FIXME: Should this be EXPAND_IF_NEEDED? `
- [ ] Linia **3385**: `     // FIXME: Should this use EXPAND_IF_NEEDED? `
- [ ] Linia **3519**: `     // FIXME: Should this use EXPAND_IF_NEEDED? `
- [ ] Linia **4184**: ` // FIXME: Check simultaneous read-write support `

## `src/gpu/SDL_gpu.c`

- [ ] Linia **24**: ` // FIXME: This could probably use SDL_ObjectValid `
- [ ] Linia **1069**: `                 // TODO: validate that format support blending? `
- [ ] Linia **1093**: `             // TODO: validate that format supports belnding? This is only required on Metal. `
- [ ] Linia **2484**: `         // TODO: validate buffer usage? `

## `src/gpu/vulkan/SDL_gpu_vulkan.c`

- [ ] Linia **203**: `         // TODO: use VK_FORMAT_A8_UNORM_KHR from VK_KHR_maintenance5 when available `
- [ ] Linia **214**: `         // TODO: use VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT from VK_EXT_4444_formats when available `
- [ ] Linia **611**: `     // FIXME: It'd be nice if we didn't have to have this on the texture... `
- [ ] Linia **6626**: `     // TODO: enable pipeline caching `
- [ ] Linia **6685**: `     // FIXME: It is uncertain if drivers are able to load both byte orders. If `
- [ ] Linia **9984**: `                 NULL, // FIXME: VAllocationCallbacks `
- [ ] Linia **10186**: `                 NULL, // FIXME: VAllocationCallbacks `
- [ ] Linia **10835**: `     // FIXME: Can this just be permanent? `
- [ ] Linia **12363**: `     // FIXME: Need better structure for checking vs storing swapchain support details `
- [ ] Linia **12881**: `             // FIXME: driverInfo can be a multiline string. `
- [ ] Linia **12911**: `     // FIXME: just move this into this function `
- [ ] Linia **12990**: `         0,  // !!! FIXME: a real guess here, for a _minimum_ if not a maximum, could be useful. `
- [ ] Linia **12998**: `         0,  // !!! FIXME: a real guess here, for a _minimum_ if not a maximum, could be useful. `
- [ ] Linia **13006**: `         0,  // !!! FIXME: a real guess here, for a _minimum_ if not a maximum, could be useful. `
- [ ] Linia **13014**: `         0,  // !!! FIXME: a real guess here, for a _minimum_ if not a maximum, could be useful. `
- [ ] Linia **13022**: `         0,  // !!! FIXME: a real guess here, for a _minimum_ if not a maximum, could be useful. `
- [ ] Linia **13030**: `         0,  // !!! FIXME: a real guess here, for a _minimum_ if not a maximum, could be useful. `

## `src/haptic/android/SDL_syshaptic.c`

- [ ] Linia **296**: `             // !!! TODO: Send a haptic remove event? `

## `src/haptic/darwin/SDL_syshaptic.c`

- [ ] Linia **317**: `             // !!! TODO: Send a haptic remove event? `

## `src/haptic/linux/SDL_syshaptic.c`

- [ ] Linia **287**: `     // TODO: should we add instance IDs? `
- [ ] Linia **297**: `     // !!! TODO: Send a haptic add event? `
- [ ] Linia **329**: `             // !!! TODO: Send a haptic remove event? `

## `src/haptic/windows/SDL_dinputhaptic.c`

- [ ] Linia **294**: `     /* !!! FIXME: opening a haptic device here first will make an attempt to `
- [ ] Linia **295**: `        !!! FIXME:  SDL_OpenJoystick() that same device fail later, since we `
- [ ] Linia **296**: `        !!! FIXME:  have it open in exclusive mode. But this will allow `
- [ ] Linia **297**: `        !!! FIXME:  SDL_OpenJoystick() followed by SDL_OpenHapticFromJoystick() `
- [ ] Linia **298**: `        !!! FIXME:  to work, and that's probably the common case. Still, `
- [ ] Linia **299**: `        !!! FIXME:  ideally, We need to unify the opening code. */ `

## `src/haptic/windows/SDL_windowshaptic.c`

- [ ] Linia **96**: `     // !!! TODO: Send a haptic remove event? `
- [ ] Linia **247**: `         // !!! FIXME: (...is leaking on purpose a good idea?) - No, of course not. `

## `src/hidapi/android/hid.cpp`

- [ ] Linia **673**: ` 				return -1; // Read already ongoing, we currently do not serialize, TODO `
- [ ] Linia **1144**: ` 	// TODO: Implement `
- [ ] Linia **1251**: ` // TODO: Implement blocking `
- [ ] Linia **1258**: ` // TODO: Implement? `

## `src/hidapi/doxygen/Doxyfile`

- [ ] Linia **704**: ` # The GENERATE_TODOLIST tag can be used to enable (YES) or disable (NO) the todo `
- [ ] Linia **705**: ` # list. This list is created by putting \todo commands in the documentation. `

## `src/hidapi/ios/hid.m`

- [ ] Linia **87**: ` // TODO: create CBUUID's in __attribute__((constructor)) rather than doing [CBUUID UUIDWithString:...] everywhere `
- [ ] Linia **438**: ` 				// TODO: we could limit our scan to only peripherals supporting the SteamController service, but `

## `src/hidapi/libusb/hid.c`

- [ ] Linia **219**: ` /*TODO: Implement this function on hidapi/libusb.. */ `
- [ ] Linia **1156**: ` 							/* TODO: have a runtime check for this section. */ `
- [ ] Linia **2327**: ` #if 0 /* TODO: Do we need this? */ `

## `src/hidapi/linux/hid.c`

- [ ] Linia **966**: ` 		/* TODO: have a better error reporting via create_device_info_for_device */ `

## `src/hidapi/mac/hid.c`

- [ ] Linia **978**: ` 	CFRunLoopStop(dev->run_loop); /*TODO: CFRunLoopGetCurrent()*/ `

## `src/hidapi/src/CMakeLists.txt`

- [ ] Linia **87**: `     # FIXME: https://github.com/libusb/hidapi/issues/492: it is untrivial to set the include path for Framework correctly `

## `src/hidapi/windows/hid.c`

- [ ] Linia **1096**: ` 	/* TODO: Merge this with the Linux version. This function is platform-independent. */ `
- [ ] Linia **1111**: ` 	/* TODO: Merge this functions with the Linux version. This function should be platform independent. */ `

## `src/io/generic/SDL_asyncio_generic.c`

- [ ] Linia **49**: `     SDL_Mutex *lock;  // !!! FIXME: we can skip this lock if we have an equivalent of pread/pwrite `
- [ ] Linia **210**: `         max_threadpool_threads = (SDL_GetNumLogicalCPUCores() * 2) + 1;  // !!! FIXME: this should probably have a hint to override. `

## `src/io/io_uring/SDL_asyncio_liburing.c`

- [ ] Linia **242**: `             // !!! FIXME: fill in task->error. `
- [ ] Linia **313**: `     for (int i = 0; i < num_waiting; i++) {  // !!! FIXME: is there a better way to do this than pushing a zero-timeout request for everything waiting? `
- [ ] Linia **357**: `     // !!! FIXME: no idea how large the queue should be. Is 128 overkill or too small? `
- [ ] Linia **386**: ``     // !!! FIXME: `unsigned` is likely smaller than requested_size's Uint64. If we overflow it, we could try submitting multiple SQEs ``
- [ ] Linia **387**: `     // !!! FIXME:  and make a note in the task that there are several in sequence. `
- [ ] Linia **412**: ``     // !!! FIXME: `unsigned` is likely smaller than requested_size's Uint64. If we overflow it, we could try submitting multiple SQEs ``
- [ ] Linia **413**: `     // !!! FIXME:  and make a note in the task that there are several in sequence. `

## `src/io/SDL_asyncio.c`

- [ ] Linia **237**: `         SDL_assert(async_close_task_was_queued);  // !!! FIXME: if this fails to queue the task, we're leaking resources! `
- [ ] Linia **327**: `             // !!! FIXME: check if flen > address space, since it'll truncate and we'll just end up with an incomplete buffer or a crash. `

## `src/io/SDL_iostream.c`

- [ ] Linia **171**: `     // FIXME: We may be able to satisfy the seek within buffered data `
- [ ] Linia **238**: ``             return 0;  // !!! FIXME: this should return the bytes read from any readahead we finished out before this (the `iodata->left > 0` code above). In that case, fail on the next read. ``
- [ ] Linia **262**: ``             return 0;  // !!! FIXME: this should return the bytes read from any readahead we finished out before this (the `iodata->left > 0` code above). In that case, fail on the next read. ``

## `src/io/windows/SDL_asyncio_windows_ioring.c`

- [ ] Linia **209**: `                 // !!! FIXME: fill in task->error. `
- [ ] Linia **320**: `     // !!! FIXME: no idea how large the queue should be. Is 128 overkill or too small? `
- [ ] Linia **382**: `     // !!! FIXME: UINT32 smaller than requested_size's Uint64. If we overflow it, we could try submitting multiple SQEs `
- [ ] Linia **383**: `     // !!! FIXME:  and make a note in the task that there are several in sequence. `
- [ ] Linia **408**: `     // !!! FIXME: UINT32 smaller than requested_size's Uint64. If we overflow it, we could try submitting multiple SQEs `
- [ ] Linia **409**: `     // !!! FIXME:  and make a note in the task that there are several in sequence. `

## `src/joystick/android/SDL_sysjoystick.c`

- [ ] Linia **67**: `  * FIXME: This is only suited for the case where we use a fixed number of buttons determined by ANDROID_MAX_NBUTTONS `
- [ ] Linia **71**: `     // FIXME: If this function gets too unwieldy in the future, replace with a lookup table `

## `src/joystick/emscripten/SDL_sysjoystick_c.h`

- [ ] Linia **46**: `     double axis[64];            // !!! FIXME: don't hardcode 64 on all of these. `

## `src/joystick/emscripten/SDL_sysjoystick.c`

- [ ] Linia **98**: `         // TODO: Safari `

## `src/joystick/gdk/SDL_gameinputjoystick.cpp`

- [ ] Linia **983**: `     // FIXME: We can poll this at a much lower rate `

## `src/joystick/hidapi/SDL_hidapi_8bitdo.c`

- [ ] Linia **290**: `     // TODO: If sensor time stamp is sent, these fixed settings from observation can be replaced `

## `src/joystick/hidapi/SDL_hidapi_gip.c`

- [ ] Linia **1231**: `         /* TODO: Implement Security command property */ `
- [ ] Linia **1312**: `     // TODO `
- [ ] Linia **1701**: `     // TODO `
- [ ] Linia **1736**: `     // TODO `
- [ ] Linia **1969**: `         // TODO `
- [ ] Linia **2413**: `     // TODO `
- [ ] Linia **2424**: `     // TODO `
- [ ] Linia **2435**: `     // TODO `
- [ ] Linia **2446**: `     // TODO `
- [ ] Linia **2590**: `                  * TODO: Is this the correct behavior? `

## `src/joystick/hidapi/SDL_hidapi_lg4ff.c`

- [ ] Linia **450**: `         // TODO do not adjust for MOMO wheels, when support is added `

## `src/joystick/hidapi/SDL_hidapi_ps4.c`

- [ ] Linia **983**: `         // FIXME: Should we send a consistent default effect mask between BT and USB? `

## `src/joystick/hidapi/SDL_hidapi_steam_hori.c`

- [ ] Linia **266**: `         // TODO: can we handle the digital trigger mode? The data seems to come through analog regardless of the trigger state `

## `src/joystick/hidapi/SDL_hidapi_switch2.c`

- [ ] Linia **325**: `     // FIXME: Need to add Bluetooth support `
- [ ] Linia **608**: `         // FIXME: How many buttons does this have? `
- [ ] Linia **1085**: `                 // FIXME: This shouldn't be necessary, but the rumble thread appears to back up if we don't do this `
- [ ] Linia **1144**: `         // FIXME: Need state handling implementation `

## `src/joystick/hidapi/SDL_hidapi_wii.c`

- [ ] Linia **1446**: `     // FIXME: This should see if the data format is compatible rather than equal `

## `src/joystick/hidapi/SDL_hidapi_zuiki.c`

- [ ] Linia **300**: `         /* todo for switch C key */ `

## `src/joystick/hidapi/SDL_hidapijoystick.c`

- [ ] Linia **1480**: `         // FIXME: The device could be freed after this name is returned... `
- [ ] Linia **1494**: `         // FIXME: The device could be freed after this path is returned... `

## `src/joystick/hidapi/steam/controller_structs.h`

- [ ] Linia **312**: ` 	// FIXME figure out a way to grab this stuff over wireless `
- [ ] Linia **358**: ` 	unsigned char ucGyroDataType; //TODO could maybe find some unused bits in the button field for this info (is only 2bits) `

## `src/joystick/linux/SDL_sysjoystick.c`

- [ ] Linia **1391**: `             // TODO: is there any way to detect analog hats in advance via this API? `

## `src/joystick/SDL_gamepad.c`

- [ ] Linia **722**: `             // FIXME: Should we have a separate hint for non-HIDAPI JoyCon handling? `
- [ ] Linia **1191**: `             // FIXME: Should we map this to the left or right side? `
- [ ] Linia **1694**: `     // FIXME: We fix these up when loading the mapping, does this ever get hit? `

## `src/joystick/SDL_joystick.c`

- [ ] Linia **91**: ` #ifdef SDL_JOYSTICK_USBHID /* !!! FIXME: "USBHID" is a generic name, and doubly-confusing with HIDAPI next to it. This is the *BSD interface, rename this. */ `

## `src/joystick/windows/SDL_windows_gaming_input.c`

- [ ] Linia **745**: `         // FIXME: Can WGI even tell us if trigger rumble is supported? `
- [ ] Linia **875**: `             // FIXME: What units are the timestamp we get from GetCurrentReading()? `

## `src/joystick/windows/SDL_xinputjoystick.c`

- [ ] Linia **398**: `     // FIXME: This does end up making a device ioctl() to query data, we shouldn't do this every update. `

## `src/libm/e_exp.c`

- [ ] Linia **132**: ` 		#else  /* !!! FIXME: check this: "huge * huge" is a compiler warning, maybe they wanted +Inf? */ `

## `src/locale/unix/SDL_syslocale.c`

- [ ] Linia **67**: `     // !!! FIXME: should we be using setlocale()? Or some D-Bus thing? `

## `src/main/gdk/SDL_sysmain_runapp.cpp`

- [ ] Linia **78**: `         // !!! FIXME: This follows the docs exactly, but for some reason still leaks handles on exit? `

## `src/main/generic/SDL_sysmain_callbacks.c`

- [ ] Linia **63**: `             // !!! FIXME: this can be made more complicated if we decide to `
- [ ] Linia **64**: `             // !!! FIXME: optionally hand off callback responsibility to the `
- [ ] Linia **65**: `             // !!! FIXME: video subsystem (for example, if Wayland has a `
- [ ] Linia **66**: `             // !!! FIXME: protocol to drive an animation loop, maybe we hand `
- [ ] Linia **67**: `             // !!! FIXME: off to them here if/when the video subsystem becomes `
- [ ] Linia **68**: `             // !!! FIXME: initialized). `

## `src/power/haiku/SDL_syspower.c`

- [ ] Linia **24**: ` // !!! FIXME: does this thing even work on Haiku? `

## `src/power/linux/SDL_syspower.c`

- [ ] Linia **150**: `             // !!! FIXME: what exactly _does_ charging/discharging mean? `
- [ ] Linia **185**: `     // !!! FIXME: calculate (secs). `

## `src/power/macos/SDL_syspower.c`

- [ ] Linia **91**: `             val = -1; // !!! FIXME: calc from timeToFull and capacity? `

## `src/power/windows/SDL_syspower.c`

- [ ] Linia **35**: `         // !!! FIXME: push GetLastError() into SDL_GetError() `

## `src/render/direct3d11/SDL_render_d3d11.c`

- [ ] Linia **48**: ` /* !!! FIXME: vertex buffer bandwidth could be lower; only use UV coords when `
- [ ] Linia **49**: `    !!! FIXME:  textures are needed. */ `
- [ ] Linia **646**: `         // FIXME: Should we use the default adapter? `
- [ ] Linia **786**: `     // FIXME `

## `src/render/direct3d12/SDL_render_d3d12.c`

- [ ] Linia **50**: ` /* !!! FIXME: vertex buffer bandwidth could be lower; only use UV coords when `
- [ ] Linia **51**: `    !!! FIXME:  textures are needed. */ `
- [ ] Linia **559**: `     // FIXME should we also clear currentSampler.ptr and currentRenderTargetView.ptr ? (and use D3D12_InvalidateCachedState() instead) `
- [ ] Linia **1166**: `     // FIXME `
- [ ] Linia **2900**: `         // FIXME: Xbox doesn't support FUNC_NONE as of the October 2025 GDK, but `

## `src/render/gpu/SDL_pipeline_gpu.c`

- [ ] Linia **145**: `         // !!! FIXME: why don't we have an SDL_alloc_copy function/macro? `

## `src/render/gpu/SDL_render_gpu.c`

- [ ] Linia **327**: `         // TODO allocate a persistent transfer buffer `
- [ ] Linia **734**: `     // *** FIXME *** `
- [ ] Linia **1159**: ` // *** FIXME *** `
- [ ] Linia **1626**: `         // FIXME should we return an error if both mailbox and immediate fail? `
- [ ] Linia **1780**: `     // FIXME: What's a good initial size? `

## `src/render/gpu/SDL_shaders_gpu.c`

- [ ] Linia **191**: `     // FIXME not sure if this is correct `

## `src/render/metal/SDL_render_metal.m`

- [ ] Linia **888**: `     /* TODO: We could have a pool of textures or a MTLHeap we allocate from, `
- [ ] Linia **921**: `     /* TODO: This isn't very efficient for the YUV formats, which call `
- [ ] Linia **1274**: `        angles. Maybe !!! FIXME for later, though. */ `
- [ ] Linia **1731**: `         // !!! FIXME: have a ring of pre-made MTLBuffers we cycle through? How expensive is creation? `
- [ ] Linia **1787**: `                     // !!! FIXME: have to commit, or an uncommitted but enqueued buffer will prevent the frame from finishing. `
- [ ] Linia **2262**: `         // !!! FIXME: error checking on all of this. `
- [ ] Linia **2377**: `         // !!! FIXME: force more clears here so all the drawables are sane to start, and our static buffers are definitely flushed. `

## `src/render/opengl/SDL_render_gl.c`

- [ ] Linia **963**: `     // TODO: check if texture pixel format allows this operation `
- [ ] Linia **973**: ` /* !!! FIXME: all these Queue* calls set up the vertex buffer the way the immediate mode `
- [ ] Linia **974**: `    !!! FIXME:  renderer wants it, but this might want to operate differently if we move to `
- [ ] Linia **975**: `    !!! FIXME:  VBOs at some point. */ `
- [ ] Linia **1356**: `     cache->vertex_array = false;  // !!! FIXME: this resets to false at the end of GL_RunCommandQueue, but we could cache this more aggressively. `
- [ ] Linia **1357**: `     cache->color_array = false;  // !!! FIXME: this resets to false at the end of GL_RunCommandQueue, but we could cache this more aggressively. `
- [ ] Linia **1358**: `     cache->texture_array = false;  // !!! FIXME: this resets to false at the end of GL_RunCommandQueue, but we could cache this more aggressively. `
- [ ] Linia **1365**: `     // !!! FIXME: it'd be nice to use a vertex buffer instead of immediate mode... `

## `src/render/ps2/SDL_render_ps2.c`

- [ ] Linia **416**: `         // FIXME: What are the settings for this? `
- [ ] Linia **429**: `         // FIXME: What are the settings for this? `
- [ ] Linia **515**: `             // FIXME: We need to update the clip rect too, see https://github.com/libsdl-org/SDL/issues/9094 `

## `src/render/psp/SDL_render_psp.c`

- [ ] Linia **1053**: `             // FIXME SDL_BLENDMODE_MUL is simplified, and dstA is in fact un-changed. `
- [ ] Linia **1125**: `         /* FIXME: Find a genuine way to make viewport work (right now calling these functions here give no effect) */ `

## `src/render/SDL_render.c`

- [ ] Linia **3136**: `         // FIXME: Are these events guaranteed to be window relative? `
- [ ] Linia **4269**: `     // We don't intersect the dstrect with the viewport as RenderCopy does because of potential rotation clipping issues... TODO: should we? `

## `src/render/software/SDL_blendfillrect.c`

- [ ] Linia **324**: `     // FIXME: Does this function pointer slow things down significantly? `

## `src/render/software/SDL_blendline.c`

- [ ] Linia **936**: `     // FIXME: We don't actually want to clip, as it may change line slope `
- [ ] Linia **969**: `         // FIXME: We don't actually want to clip, as it may change line slope `

## `src/render/software/SDL_blendpoint.c`

- [ ] Linia **320**: `     // FIXME: Does this function pointer slow things down significantly? `

## `src/render/software/SDL_drawline.c`

- [ ] Linia **150**: `     // FIXME: We don't actually want to clip, as it may change line slope `
- [ ] Linia **183**: `         // FIXME: We don't actually want to clip, as it may change line slope `

## `src/render/software/SDL_render_sw.c`

- [ ] Linia **677**: `     // !!! FIXME: we can probably avoid some of these calls. `

## `src/render/vitagxm/SDL_render_vita_gxm.c`

- [ ] Linia **1177**: `     // TODO: read from texture rendertarget. `

## `src/SDL_assert.c`

- [ ] Linia **205**: `             // !!! FIXME: ungrab the input if we're not fullscreen? `

## `src/SDL_hashtable.c`

- [ ] Linia **25**: `     // TODO: Splitting off values into a separate array might be more cache-friendly `

## `src/SDL_hashtable.h`

- [ ] Linia **261**: ``  * !!! FIXME: add note about `threadsafe` here. And update `threadsafety` tags. ``
- [ ] Linia **262**: ``  * !!! FIXME: note that `threadsafe` tables can't be recursively locked, so ``
- [ ] Linia **263**: ``  * !!! FIXME:  you can't use `destroy` callbacks that might end up relocking. ``

## `src/SDL_utils.c`

- [ ] Linia **593**: `                 // FIXME: Need to handle the expand case by reallocating the string `

## `src/sensor/android/SDL_androidsensor.c`

- [ ] Linia **145**: `     // FIXME: Is the sensor list dynamic? `
- [ ] Linia **223**: `         // FIXME: Maybe add a hint for this? `

## `src/sensor/windows/SDL_windowssensor.c`

- [ ] Linia **202**: `                     // FIXME: Need to know how to interpret the data for this sensor `

## `src/stdlib/SDL_getenv.c`

- [ ] Linia **61**: `     SDL_Mutex *lock;   // !!! FIXME: reuse SDL_HashTable's lock. `
- [ ] Linia **102**: `     // Don't fail if we can't create a mutex (e.g. on a single-thread environment)  // !!! FIXME: single-threaded environments should still return a non-NULL, do-nothing object here. Check for failure! `
- [ ] Linia **280**: `                     // !!! FIXME: InsertIntoHashTable does this lookup too, maybe we should have a means to report that, to avoid duplicate work? `

## `src/stdlib/SDL_string.c`

- [ ] Linia **86**: `     // !!! FIXME: since the hashtable is static, maybe we should binary `
- [ ] Linia **87**: `     // !!! FIXME: search it instead of walking the whole bucket. `
- [ ] Linia **1512**: `             // FIXME: implement more of the format specifiers `
- [ ] Linia **1840**: ` // FIXME: implement more of the format specifiers `

## `src/storage/generic/SDL_genericstorage.c`

- [ ] Linia **129**: `             // FIXME: Should SDL_ReadIO use u64 now...? `
- [ ] Linia **144**: `     // TODO: Recursively create subdirectories with SDL_CreateDirectory `
- [ ] Linia **156**: `             // FIXME: Should SDL_WriteIO use u64 now...? `
- [ ] Linia **171**: `     // TODO: Recursively create subdirectories with SDL_CreateDirectory `
- [ ] Linia **228**: `     // TODO: There's totally a way to query a folder root's quota... `

## `src/storage/steam/SDL_steamstorage.c`

- [ ] Linia **43**: ` // !!! FIXME: Async API can use SteamRemoteStorage_ReadFileAsync `
- [ ] Linia **44**: ` // !!! FIXME: Async API can use SteamRemoteStorage_WriteFileAsync `

## `src/test/SDL_test_common.c`

- [ ] Linia **94**: ` /* !!! FIXME: Float32? Sint32? */ `

## `src/thread/generic/SDL_sysrwlock.c`

- [ ] Linia **33**: ` // !!! FIXME: this is quite a tapdance with macros and the build system, maybe we can simplify how we do this. --ryan. `
- [ ] Linia **99**: `         // !!! FIXME: these don't have to be atomic, we always gate them behind a mutex. `
- [ ] Linia **128**: `             // !!! FIXME: there is a small window where a reader has to lock the mutex, and if we hit that, we will return SDL_RWLOCK_TIMEDOUT even though we could have shared the lock. `

## `src/thread/ps2/SDL_syssem.c`

- [ ] Linia **46**: `         // TODO: Figure out the limit on the maximum value. `

## `src/thread/psp/SDL_syssem.c`

- [ ] Linia **45**: `         // TODO: Figure out the limit on the maximum value. `
- [ ] Linia **70**: ` /* TODO: This routine is a bit overloaded. `

## `src/thread/psp/SDL_systhread.c`

- [ ] Linia **93**: `     // !!! FIXME: is this correct? `

## `src/thread/pthread/SDL_systhread.c`

- [ ] Linia **191**: `     // FIXME: Setting thread priority does not seem to be supported `

## `src/thread/vita/SDL_syssem.c`

- [ ] Linia **46**: `         // TODO: Figure out the limit on the maximum value. `
- [ ] Linia **71**: ` /* TODO: This routine is a bit overloaded. `

## `src/time/ps2/SDL_systime.c`

- [ ] Linia **30**: ` // TODO: Implement this... `
- [ ] Linia **52**: `     // FIXME: Need implementation `

## `src/video/android/SDL_androidpen.c`

- [ ] Linia **48**: `         // TODO: Query JNI for pen device info `
- [ ] Linia **64**: `     // TODO: add more axis `

## `src/video/cocoa/SDL_cocoaevents.m`

- [ ] Linia **333**: `         SDL_Delay(300); // !!! FIXME: this isn't right. `
- [ ] Linia **444**: `     // !!! FIXME: Menu items can't take parameters, just a basic selector, so this should instead call a selector `
- [ ] Linia **445**: `     // !!! FIXME: that itself calls -[NSApplication orderFrontStandardAboutPanelWithOptions:optionsDictionary], `
- [ ] Linia **446**: `     // !!! FIXME: filling in that NSDictionary with SDL_GetAppMetadataProperty() `
- [ ] Linia **668**: `             /* FIXME: this should ideally describe the real reason why the game `

## `src/video/cocoa/SDL_cocoamodes.m`

- [ ] Linia **85**: `     // !!! FIXME: maybe track the NSScreen in SDL_DisplayData? `

## `src/video/cocoa/SDL_cocoamouse.m`

- [ ] Linia **180**: `         case SDL_SYSTEM_CURSOR_WAIT: // !!! FIXME: this is more like WAITARROW `
- [ ] Linia **183**: `         case SDL_SYSTEM_CURSOR_PROGRESS: // !!! FIXME: this is meant to be animated `

## `src/video/cocoa/SDL_cocoaopengl.m`

- [ ] Linia **96**: `         // !!! FIXME: check return values. `

## `src/video/cocoa/SDL_cocoaopengles.m`

- [ ] Linia **126**: ` // !!! FIXME: commenting out this assertion is (I think) incorrect; figure out why driver_loaded is wrong for ANGLE instead. --ryan. `

## `src/video/cocoa/SDL_cocoavulkan.m`

- [ ] Linia **222**: `      * TODO: Now that we have SDL_Vulkan_DestroySurface someone with enough `
- [ ] Linia **300**: `         // TODO: Add CFBridgingRelease(metalview) here perhaps? `

## `src/video/cocoa/SDL_cocoawindow.m`

- [ ] Linia **332**: `     // !!! FIXME: is there a better way to do this? `
- [ ] Linia **549**: ` // !!! FIXME: this should use a hint callback. `
- [ ] Linia **1616**: `         // FIXME: Why does the window get hidden? `
- [ ] Linia **2088**: `         /* TODO: Before implementing direct touch support here, we need to `
- [ ] Linia **2367**: `             /* FIXME: Should not need to call addChildWindow then orderOut. `

## `src/video/emscripten/SDL_emscriptenevents.c`

- [ ] Linia **1374**: `     // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do: `
- [ ] Linia **1375**: `     // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621 `
- [ ] Linia **1378**: `     // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do: `
- [ ] Linia **1386**: `     // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do: `
- [ ] Linia **1389**: `     // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do: `
- [ ] Linia **1390**: `     // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621 `

## `src/video/emscripten/SDL_emscriptenframebuffer.c`

- [ ] Linia **77**: `         //TODO: this should store a context per canvas `

## `src/video/emscripten/SDL_emscriptenmouse.c`

- [ ] Linia **179**: `     // TODO: pointer lock isn't actually enabled yet `

## `src/video/emscripten/SDL_emscriptenvideo.c`

- [ ] Linia **229**: `         // TODO: Handle parent window when multiple windows can be added in Emscripten builds `
- [ ] Linia **574**: `         window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;   // !!! FIXME: should this fail instead? `

## `src/video/gdk/SDL_gdktextinput.cpp`

- [ ] Linia **45**: ` // TODO: Have a separate task queue for text input perhaps? `
- [ ] Linia **282**: `         // FIXME: Password or number scope? `

## `src/video/haiku/SDL_bmessagebox.cc`

- [ ] Linia **189**: ` 		// TODO: Not Implemented. `

## `src/video/haiku/SDL_bmodes.cc`

- [ ] Linia **41**: ` #define WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary `
- [ ] Linia **79**: ` /* TODO: `
- [ ] Linia **213**: `     /* TODO: When Haiku supports multiple display screens, call `
- [ ] Linia **252**: `         // FIXME: Apparently there are errors with colorspace changes `
- [ ] Linia **275**: `     // FIXME: Is the first option always going to be the right one? `
- [ ] Linia **295**: `     /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't `

## `src/video/haiku/SDL_bopengl.cc`

- [ ] Linia **51**: ` // FIXME: Is this working correctly? `
- [ ] Linia **111**: `     /* FIXME: Not sure what flags should be included here; may want to have `
- [ ] Linia **166**: `     // TODO: Implement this, if necessary? `
- [ ] Linia **178**: `     // TODO: Implement this, if necessary? `
- [ ] Linia **182**: ` /* FIXME: This function is meant to clear the OpenGL context when the video `

## `src/video/haiku/SDL_bopengl.h`

- [ ] Linia **33**: ` extern bool HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, const char *path);      // FIXME `
- [ ] Linia **34**: ` extern SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, const char *proc); // FIXME `
- [ ] Linia **35**: ` extern void HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this);                     // TODO `
- [ ] Linia **38**: ` extern bool HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, int interval); // TODO `
- [ ] Linia **39**: ` extern bool HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, int *interval); // TODO `

## `src/video/haiku/SDL_bvideo.cc`

- [ ] Linia **57**: `     device->internal = NULL; /* FIXME: Is this the cause of some of the `
- [ ] Linia **60**: ` // TODO: Figure out if any initialization needs to go here `

## `src/video/haiku/SDL_BWin.h`

- [ ] Linia **530**: `         /* FIXME: Why were these here? `
- [ ] Linia **741**: ` /* FIXME: `

## `src/video/haiku/SDL_bwindow.cc`

- [ ] Linia **57**: `         // TODO: Add support for this flag `
- [ ] Linia **60**: `         // TODO: Add support for this flag `
- [ ] Linia **186**: `     // TODO: Implement this! `

## `src/video/kmsdrm/SDL_kmsdrmmouse.c`

- [ ] Linia **35**: ` // !!! FIXME: atomic cursors are broken right now. `
- [ ] Linia **458**: `     // TODO: ? `
- [ ] Linia **479**: `             /* !!! FIXME: Some programs expect cursor movement even while they don't do SwapWindow() calls, `

## `src/video/kmsdrm/SDL_kmsdrmopengles.c`

- [ ] Linia **202**: `     info.src_w = window->w;  // !!! FIXME: was windata->src_w in the original atomic patch `
- [ ] Linia **203**: `     info.src_h = window->h;  // !!! FIXME: was windata->src_h in the original atomic patch `
- [ ] Linia **204**: `     info.crtc_w = dispdata->mode.hdisplay;  // !!! FIXME: was windata->output_w in the original atomic patch `
- [ ] Linia **205**: `     info.crtc_h = dispdata->mode.vdisplay;  // !!! FIXME: was windata->output_h in the original atomic patch `
- [ ] Linia **206**: `     info.crtc_x = 0;  // !!! FIXME: was windata->output_x in the original atomic patch `
- [ ] Linia **347**: `     info.src_w = window->w;  // !!! FIXME: was windata->src_w in the original atomic patch `
- [ ] Linia **348**: `     info.src_h = window->h;  // !!! FIXME: was windata->src_h in the original atomic patch `
- [ ] Linia **349**: `     info.crtc_w = dispdata->mode.hdisplay;  // !!! FIXME: was windata->output_w in the original atomic patch `
- [ ] Linia **350**: `     info.crtc_h = dispdata->mode.vdisplay;  // !!! FIXME: was windata->output_h in the original atomic patch `
- [ ] Linia **351**: `     info.crtc_x = 0;  // !!! FIXME: was windata->output_x in the original atomic patch `

## `src/video/kmsdrm/SDL_kmsdrmvideo.c`

- [ ] Linia **1614**: `     /* TODO : Continue investigating why this doesn't work. We should do this instead `
- [ ] Linia **1618**: ` #if 0  // (note that this code has bitrotted a little, in addition to TODO comment above.) `
- [ ] Linia **1800**: `        FIXME: How do we do that now? Can we get a better idea at the higher level? `

## `src/video/miniz.h`

- [ ] Linia **213**: `   // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux `
- [ ] Linia **1452**: ` // TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never `
- [ ] Linia **3570**: `   // FIXME: Remove this check? Is it necessary - we already check the filename. `

## `src/video/psp/SDL_pspvideo.c`

- [ ] Linia **138**: ` 	// TODO: understand how these work `

## `src/video/qnx/SDL_qnxgl.c`

- [ ] Linia **230**: `     // !!! FIXME: should we migrate this all over to use SDL_egl.c? `

## `src/video/qnx/SDL_qnxkeyboard.c`

- [ ] Linia **125**: `     // FIXME: `

## `src/video/raspberry/SDL_rpimouse.c`

- [ ] Linia **286**: `     /* FIXME: Using UDEV it should be possible to scan all mice `

## `src/video/riscos/SDL_riscosvideo.c`

- [ ] Linia **90**: `     // TODO: Support windowed mode `

## `src/video/SDL_blit_N.c`

- [ ] Linia **871**: ` // !!!! FIXME: Check for G5 or later, not the cache size! Always prefetch on a G4. `

## `src/video/SDL_blit.h`

- [ ] Linia **338**: ` // FIXME: Should we rescale alpha into 0..255 here? `
- [ ] Linia **444**: ` // FIXME: this isn't correct, especially for Alpha (maximum != 255) `
- [ ] Linia **524**: ` // FIXME: SDL_SIZE_MAX might not be an integer literal `

## `src/video/SDL_bmp.c`

- [ ] Linia **134**: `                 // !!! FIXME: this needsPad calculation can probably be simpler than this. `

## `src/video/SDL_egl.c`

- [ ] Linia **1201**: `     /* FIXME: Revisit this check when EGL_EXT_swap_control_tear is published: `

## `src/video/SDL_stb.c`

- [ ] Linia **291**: `             /* FIXME: This sucks. It'd be better to allocate the surface first, then `
- [ ] Linia **324**: `             /* FIXME: This sucks. It'd be better to allocate the surface first, then `

## `src/video/SDL_surface.c`

- [ ] Linia **2825**: `         // FIXME: We need code to extract a single macroblock from a YUV surface `
- [ ] Linia **2902**: `         // FIXME: We need code to extract a single macroblock from a YUV surface `

## `src/video/SDL_video.c`

- [ ] Linia **3623**: ` #if defined(SDL_PLATFORM_WIN32) || defined(SDL_PLATFORM_WINGDK) // GDI BitBlt() is way faster than Direct3D dynamic textures right now. (!!! FIXME: is this still true?) `
- [ ] Linia **3651**: `                 /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc), `
- [ ] Linia **3652**: `                    !!! FIXME:  we probably need to clean this up so it doesn't interfere with `
- [ ] Linia **3653**: `                    !!! FIXME:  a software fallback at the system level (can we blit to an `
- [ ] Linia **3654**: `                    !!! FIXME:  OpenGL window? etc). */ `
- [ ] Linia **3657**: `                 /* !!! FIXME:  maybe we shouldn't override these but check if we used a texture `
- [ ] Linia **3658**: `                    !!! FIXME:  framebuffer at the right places; is it feasible we could have an `
- [ ] Linia **3659**: `                    !!! FIXME:  accelerated OpenGL window and a second ends up in software? */ `
- [ ] Linia **4385**: `      * FIXME: Is this fine to just remove this, or should it be preserved just `
- [ ] Linia **5271**: `         // FIXME: How do we get this information? `
- [ ] Linia **5640**: ` #if 0 // FIXME `

## `src/video/stb_image.h`

- [ ] Linia **1386**: `    // @TODO: move stbi__convert_format to here `
- [ ] Linia **1412**: `    // @TODO: move stbi__convert_format to here `
- [ ] Linia **1439**: `    // @TODO: move stbi__convert_format16 to here `
- [ ] Linia **1440**: `    // @TODO: special case RGB-to-Y (and RGBA-to-YA) for 8-bit-to-16-bit case to keep more precision `
- [ ] Linia **2158**: `    int restart_interval, todo; `
- [ ] Linia **3106**: `    j->todo = j->restart_interval ? j->restart_interval : 0x7fffffff; `
- [ ] Linia **3132**: `                if (--z->todo <= 0) { `
- [ ] Linia **3164**: `                if (--z->todo <= 0) { `
- [ ] Linia **3195**: `                if (--z->todo <= 0) { `
- [ ] Linia **3224**: `                if (--z->todo <= 0) { `
- [ ] Linia **6164**: `    STBI_NOTUSED(tga_x_origin); // @TODO `
- [ ] Linia **6165**: `    STBI_NOTUSED(tga_y_origin); // @TODO `

## `src/video/uikit/SDL_uikitappdelegate.m`

- [ ] Linia **679**: `     // TODO: Handle options `

## `src/video/uikit/SDL_uikitclipboard.m`

- [ ] Linia **91**: `                                             // TODO: compute mime types `

## `src/video/uikit/SDL_uikitmetalview.m`

- [ ] Linia **102**: `             // TODO: Consider making this configurable or determining it dynamically `

## `src/video/uikit/SDL_uikitpen.m`

- [ ] Linia **125**: `         const float rotation = rollAngle * radians_to_degrees;  // !!! FIXME: this might need adjustment, I don't have a pencil that supports it. `
- [ ] Linia **168**: `     // !!! FIXME: no timestamp on these...? `

## `src/video/uikit/SDL_uikitview.m`

- [ ] Linia **359**: `         // FIXME, need to send: int clicks = (int) touch.tapCount; ? `
- [ ] Linia **395**: `         // FIXME, need to send: int clicks = (int) touch.tapCount; ? `

## `src/video/uikit/SDL_uikitviewcontroller.m`

- [ ] Linia **172**: `     displayLink.preferredFramesPerSecond = 90 / animationInterval;      //TODO: Get frame max frame rate on visionOS `

## `src/video/uikit/SDL_uikitvulkan.m`

- [ ] Linia **246**: `      * TODO: Now that we have SDL_Vulkan_DestroySurface someone with enough `
- [ ] Linia **260**: `         // TODO: Add CFBridgingRelease(metalview) here perhaps? `

## `src/video/vivante/SDL_vivantevideo.c`

- [ ] Linia **154**: `     // FIXME: How do we query refresh rate? `
- [ ] Linia **324**: `     // FIXME `
- [ ] Linia **330**: `     // FIXME `

## `src/video/wayland/SDL_waylandevents.c`

- [ ] Linia **1725**: `      * TODO: Use a better method of detection? `
- [ ] Linia **2163**: `     // TODO: Can this happen? `
- [ ] Linia **2766**: `         // TODO: SDL Support more mime types `
- [ ] Linia **2897**: `         // TODO: SDL Support more mime types `
- [ ] Linia **3108**: `     // FIXME: Do we care about this event? `
- [ ] Linia **3440**: `     // !!! FIXME: Should hit testing be done if pens generate pointer motion? `
- [ ] Linia **3446**: `             SDL_SendPenTouch(timestamp, instance_id, window, false, true);  // !!! FIXME: how do we know what tip is in use? `
- [ ] Linia **3448**: `             SDL_SendPenTouch(timestamp, instance_id, window, false, false); // !!! FIXME: how do we know what tip is in use? `
- [ ] Linia **3453**: `             SDL_SendPenTouch(timestamp, instance_id, window, false, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);  // !!! FIXME: how do we know what tip is in use? `

## `src/video/wayland/SDL_waylandmouse.c`

- [ ] Linia **1429**: ` #if 0  // TODO RECONNECT: See waylandvideo.c for more information! `

## `src/video/wayland/SDL_waylandmouse.h`

- [ ] Linia **37**: ` #if 0  // TODO RECONNECT: See waylandvideo.c for more information! `

## `src/video/wayland/SDL_waylandopengles.c`

- [ ] Linia **96**: `     // !!! FIXME: technically, this should be per-context, right? `
- [ ] Linia **122**: `      * FIXME: Request EGL_WAYLAND_swap_buffers_with_timeout. `

## `src/video/wayland/SDL_waylandsym.h`

- [ ] Linia **95**: ` #if 0 // TODO RECONNECT: See waylandvideo.c for more information! `

## `src/video/wayland/SDL_waylandvideo.c`

- [ ] Linia **1721**: ` #if 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed `

## `src/video/wayland/SDL_waylandwindow.c`

- [ ] Linia **1922**: `      * FIXME: This was originally moved to HideWindow, which _should_ make `

## `src/video/windows/SDL_windowsevents.c`

- [ ] Linia **379**: `          * FIXME: Update keyboard state `
- [ ] Linia **2189**: `                     /* TODO: Can we use GetRawInputDeviceInfo and HID info to `
- [ ] Linia **2208**: `                     // FIXME: Should we use the input->dwTime field for the tick source of the timestamp? `
- [ ] Linia **2728**: `     // TODO: can this go before clipcursor? `

## `src/video/windows/SDL_windowsgameinput.cpp`

- [ ] Linia **358**: `         // FIXME: We probably need to track key state by keyboardID `

## `src/video/windows/SDL_windowskeyboard.c`

- [ ] Linia **618**: `     // FIXME: What does this do? `

## `src/video/windows/SDL_windowsmodes.c`

- [ ] Linia **91**: `         // FIXME: Can we tell what this will be? `

## `src/video/windows/SDL_windowsopengl.c`

- [ ] Linia **274**: `    FIXME: Should we weight any particular attribute over any other? `

## `src/video/windows/SDL_windowsopengles.c`

- [ ] Linia **114**: ` // !!! FIXME: commenting out this assertion is (I think) incorrect; figure out why driver_loaded is wrong for ANGLE instead. --ryan. `

## `src/video/windows/SDL_windowswindow.c`

- [ ] Linia **749**: `             /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The `
- [ ] Linia **759**: `     // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs) `

## `src/video/x11/edid-parse.c`

- [ ] Linia **237**: `     /* FIXME: In 1.3 this indicates whether the monitor accepts GTF */ `

## `src/video/x11/SDL_x11events.c`

- [ ] Linia **669**: `     // !!! FIXME: we need to regrab this if necessary when the drag is done. `
- [ ] Linia **704**: `     // !!! FIXME: we need to regrab this if necessary when the drag is done. `
- [ ] Linia **840**: `         /* !!! FIXME: We were probably storing this on the root window `
- [ ] Linia **867**: `                     // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do. `
- [ ] Linia **1043**: `     // FIXME: Get the event time in the SDL tick time base `
- [ ] Linia **2337**: `     // FIXME: Only need to do this when there are pending focus changes `
- [ ] Linia **2340**: `     // FIXME: Only need to do this when there are flashing windows `

## `src/video/x11/SDL_x11keyboard.c`

- [ ] Linia **87**: `         // TODO: Handle groups on the legacy path. `

## `src/video/x11/SDL_x11modes.c`

- [ ] Linia **252**: `     // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function. `
- [ ] Linia **1008**: ` // !!! FIXME: remove this later when we have a better solution. `
- [ ] Linia **1085**: `         /* !!! FIXME: this can get into a problem scenario when a window is `

## `src/video/x11/SDL_x11mouse.c`

- [ ] Linia **38**: ` // FIXME: Find a better place to put this... `
- [ ] Linia **358**: `     // FIXME: Is there a better way than this? `
- [ ] Linia **502**: `     // !!! FIXME: should we XSync() here first? `
- [ ] Linia **509**: `     // !!! FIXME: can we just calculate this from XInput's events? `

## `src/video/x11/SDL_x11opengl.c`

- [ ] Linia **447**: `         // !!! FIXME: it would be nice not to make a context here though! `

## `src/video/x11/SDL_x11pen.c`

- [ ] Linia **253**: `             // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now. `

## `src/video/x11/SDL_x11toolkit.c`

- [ ] Linia **348**: `             /* TODO: What to do the XFontSet happens to have more than one Thai font? */ `
- [ ] Linia **366**: `                 /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */ `

## `src/video/x11/SDL_x11window.c`

- [ ] Linia **170**: `     // !!! FIXME: just dereference videodata below instead of copying to locals. `
- [ ] Linia **366**: `     // FIXME, check the size hints for resizable `

## `src/video/x11/SDL_x11xinput2.c`

- [ ] Linia **241**: `      * FIXME:event and err are not needed but if not passed X11_XQueryExtension returns SegmentationFault `
- [ ] Linia **501**: `     // !!! FIXME: the pen code used to rescan all devices here, but we can do this device-by-device with XI_HierarchyChanged. When do these events fire and why? `

## `test/CMakeLists.txt`

- [ ] Linia **230**: `     # FIXME: only add "${SDL3_BINARY_DIR}/include-config-$<LOWER_CASE:$<CONFIG>>" + include paths of external dependencies `

## `test/emscripten/driver.py`

- [ ] Linia **86**: `             # FIXME: switch context, verify text of dialog and answer "a" for abort `

## `test/gamepadutils.c`

- [ ] Linia **696**: `         const Sint16 deadzone = 8000; /* !!! FIXME: real deadzone */ `

## `test/testaudiohotplug.c`

- [ ] Linia **88**: `                     /* !!! FIXME: laziness, this used to loop the audio, but we'll just play it once for now on each connect. */ `
- [ ] Linia **92**: `                     /* !!! FIXME: this is leaking the stream for now. We'll wire it up to a dictionary or whatever later. */ `
- [ ] Linia **98**: `             /* !!! FIXME: we need to keep track of our streams and destroy them here. */ `

## `test/testaudiorecording.c`

- [ ] Linia **204**: `     SDL_CloseAudioDevice(devid_in);  /* !!! FIXME: use SDL_OpenAudioDeviceStream instead so we can dump this. */ `

## `test/testautomation_audio.c`

- [ ] Linia **51**: ` #if 0  /* !!! FIXME: maybe update this? */ `
- [ ] Linia **308**: ` #if 0  /* !!! FIXME: maybe update this? */ `
- [ ] Linia **1520**: ` /* TODO: enable test when SDL_AudioDeviceConnected has been implemented.           */ `

## `test/testautomation_intrinsics.c`

- [ ] Linia **15**: ` // FIXME: missing tests for loongarch lsx/lasx `
- [ ] Linia **16**: ` // FIXME: missing tests for powerpc altivec `

## `test/testautomation_mouse.c`

- [ ] Linia **492**: `             /* TODO: add tracking of events and check that each call generates a mouse motion event */ `

## `test/testautomation_platform.c`

- [ ] Linia **177**: `     /* TODO: independently determine and compare values as well */ `

## `test/testautomation_video.c`

- [ ] Linia **2114**: `      * FIXME: Maximizing Win32 borderless windows is broken, so this always fails. `

## `test/testcamera.c`

- [ ] Linia **255**: `             /* !!! FIXME: only flip if clicked in the area of a "flip" icon. */ `
- [ ] Linia **376**: `     /* !!! FIXME: Render a "flip" icon if front_camera and back_camera are both != 0. */ `

## `test/testevdev.c`

- [ ] Linia **45**: ` /* FIXME: Need CMake tests for this */ `
- [ ] Linia **92**: `     const char *todo; `
- [ ] Linia **860**: `       /* TODO: The data I have for Steam Deck LCD didn't seem to have `
- [ ] Linia **1526**: `       /* TODO: Should this be JOYSTICK, or even JOYSTICK|HAS_KEYS? */ `
- [ ] Linia **1591**: `       /* TODO: Should this be JOYSTICK? It has one stick and two buttons */ `
- [ ] Linia **1612**: `       /* TODO: Should this be JOYSTICK, or maybe JOYSTICK|HAS_KEYS? `
- [ ] Linia **1636**: `       /* TODO: Should this be JOYSTICK? */ `
- [ ] Linia **1997**: `       /* TODO: Ideally we would identify this as a joystick, but there `
- [ ] Linia **2001**: `       .todo = "https://github.com/ValveSoftware/Proton/issues/5126", `
- [ ] Linia **2015**: `       /* TODO: Ideally we would identify this as a joystick, but there `
- [ ] Linia **2019**: `       .todo = "https://github.com/ValveSoftware/Proton/issues/5126", `
- [ ] Linia **2033**: `       /* TODO: Ideally we would identify this as a joystick by it having `
- [ ] Linia **2036**: `       .todo = "https://github.com/ValveSoftware/Proton/issues/5126", `
- [ ] Linia **2053**: `       /* TODO: Ideally we would identify this as a joystick, but there `
- [ ] Linia **2057**: `       .todo = "https://github.com/ValveSoftware/Proton/issues/5126", `
- [ ] Linia **2069**: `       /* TODO: Ideally we would identify this as a joystick, but there `
- [ ] Linia **2073**: `       .todo = "https://github.com/ValveSoftware/Proton/issues/5126", `
- [ ] Linia **2205**: `             if (t->todo) { `
- [ ] Linia **2206**: `                 printf("\tKnown issue, ignoring: %s\n", t->todo); `

## `test/testffmpeg.c`

- [ ] Linia **1014**: `         /* FIXME: We can actually keep a cache of textures that map to pixel buffers */ `

## `test/testfilesystem.c`

- [ ] Linia **173**: `         /* !!! FIXME: put this in a subroutine and make it test more thoroughly (and put it in testautomation). */ `

## `test/testmultiaudio.c`

- [ ] Linia **52**: ` #ifdef SDL_PLATFORM_ANDROID  /* !!! FIXME: maybe always create a window, in the SDLTest layer, so these #ifdefs don't have to be here? */ `

## `test/testprocess.c`

- [ ] Linia **12**: `  * FIXME: Additional tests: `
- [ ] Linia **485**: `         /* FIXME: this needs a rate limit */ `
- [ ] Linia **837**: `     /* FIXME: remove child.bat at end of loop and/or create in temporary directory */ `

## `test/testtray.c`

- [ ] Linia **575**: `     /* TODO: Track memory! */ `

## `Xcode/XcodeDocSet/Doxyfile`

- [ ] Linia **446**: ` # disable (NO) the todo list. This list is created by putting \todo  `
