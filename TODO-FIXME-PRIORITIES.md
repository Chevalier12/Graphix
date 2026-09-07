# Priorități TODO / FIXME — întregul SDL

Clasificare provizorie pentru toate platformele și backendurile, bazată pe [TODO-FIXME-CHECKLIST.md](TODO-FIXME-CHECKLIST.md), la 2026-09-07. Nu prioritizează exclusiv Graphix, Windows sau GPU.

## Sursă și limite

- Sunt păstrate **703 intrări**, din **258 de fișiere**, fiecare exact o dată și cu `[ ]` nebifat. ID-urile C0001–C0703 urmează ordinea din checklist-ul sursă.
- Textul fiecărei intrări și numărul liniei sunt copiate din checklist, nu regenerate printr-o căutare care ar include rapoartele însele. Comentariile multilinie pot produce mai multe intrări pentru aceeași problemă.
- SHA-256 al checklist-ului sursă: `A741CD04BFB2E2D0A8A2144AD90CFF00523F0CF8872AF2596F1E0675551D3374`.
- Prioritățile indică **ordinea de triere/investigare**, nu severități de bug confirmate și nici autorizație de implementare. Au fost citite toate intrările; s-a inspectat punctual contextul unor marcaje fără explicație. Nu s-au rulat reproduceri, teste runtime sau audituri de securitate.
- Numerele liniilor sunt cele din snapshot; linkurile către cod pot necesita ajustare dacă acesta se schimbă. Linkurile externe din comentarii nu au fost verificate.
- Nicio platformă și nicio bibliotecă inclusă nu este retrogradată automat pentru popularitate sau origine. Pentru codul terț, verificați ownership-ul și posibilitatea rezolvării upstream înainte de patch.
- MEDIUM este și nivelul provizoriu pentru marcaje cu impact neclar; acesta nu dovedește un risc moderat. LOW include explicit falsele pozitive și șabloanele de migrare, păstrate pentru acoperire, nu propuse spre ștergere.
- Raportul moștenește limitele inventarului sursă: nu adaugă fișiere ascunse/ignorate și nici comentarii fără TODO/FIXME.

## Criterii

| Prioritate | Criteriu și acțiune | Intrări |
|---|---|---:|
| URGENT | Securitate sau pierdere de date demonstrate, cu expunere actuală ce cere intervenție imediată. Inventarul singur nu îndeplinește acest prag. | 0 |
| HIGH | Indicii de crash, lifetime/concurență, I/O incorect, blocare sau rezultate funcționale/vizuale greșite. Reproduceți cu prioritate. | 70 |
| MEDIUM | Funcționalități incomplete, compatibilitate, performanță de măsurat, teste lipsă ori impact încă neclar. | 422 |
| LOW | Cleanup, diagnostic, documentație obișnuită, extensii opționale și potriviri care nu reprezintă sarcini distincte. | 211 |

## Cum se folosește

Începeți cu HIGH: validați contractul și dacă marcajul mai este actual, construiți reproducerea, apoi decideți fixul. Escaladați la URGENT când dovezile stabilesc impactul cerut; retrogradați când există deja o protecție corectă. Pentru optimizări, măsurați înainte de modificare. Bifați numai după rezolvare verificată sau închidere explicit justificată. Consolidarea mai multor linii într-un singur issue trebuie să păstreze toate ID-urile sursă.

**Verificarea raportului:** corespondență exactă fișier/linie/text cu toate cele 703 intrări sursă, fără omisiuni sau dublări; toate căsuțele nebifate; ID-uri unice; totaluri pe priorități reconciliate; checklist-ul sursă nemodificat.

## URGENT

Nicio intrare clasificată URGENT pe baza dovezilor disponibile. **Nu este o declarație că SDL nu are vulnerabilități sau riscuri de pierdere de date.** Semnalele potențiale sunt în HIGH până la verificare.

## HIGH

### `src/audio/aaudio/SDL_aaudio.c`

- [ ] Linia **274**: `             // !!! FIXME: also, will this definitely wait for a running data callback to finish, and then stop the callback from firing again? `
  - **C0101** · [Cod, linia 274](src/audio/aaudio/SDL_aaudio.c#L274) · Motiv: Închiderea versus callback-ul activ: risc potențial de lifetime/concurență, nu defect confirmat.

### `src/audio/n3ds/SDL_n3dsaudio.c`

- [ ] Linia **188**: `         return true;  // !!! FIXME: is this a fatal error? If so, this should return false. `
  - **C0119** · [Cod, linia 188](src/audio/n3ds/SDL_n3dsaudio.c#L188) · Motiv: Posibilă eroare fatală raportată ca succes; verificați propagarea erorilor.

### `src/audio/SDL_audio.c`

- [ ] Linia **1288**: `                 // !!! FIXME: we can't promise the device buf is aligned/padded for SIMD. `
  - **C0137** · [Cod, linia 1288](src/audio/SDL_audio.c#L1288) · Motiv: Alinierea/padding-ul SIMD nu sunt garantate în comentariu; verificare prioritară a accesului la memorie.

- [ ] Linia **2125**: ` // !!! FIXME: this and BindAudioStreams are mutex nightmares.  :/ `
  - **C0139** · [Cod, linia 2125](src/audio/SDL_audio.c#L2125) · Motiv: Locking complex semnalat explicit; audit al ordinii mutexurilor, fără deadlock demonstrat.

### `src/audio/sndio/SDL_sndioaudio.c`

- [ ] Linia **186**: `     // !!! FIXME: this should be non-blocking so we can check device->shutdown. `
  - **C0159** · [Cod, linia 186](src/audio/sndio/SDL_sndioaudio.c#L186) · Motiv: Operația blocantă împiedică verificarea shutdown; investigați oprirea blocată.

### `src/camera/SDL_camera.c`

- [ ] Linia **245**: ` // !!! FIXME: the close_cond stuff from audio might help the race condition here. `
  - **C0183** · [Cod, linia 245](src/camera/SDL_camera.c#L245) · Motiv: Comentariul semnalează o race condition; reproducere deterministă a închiderii/lifetime-ului.

### `src/core/android/SDL_android.c`

- [ ] Linia **3366**: `         // TODO: Fix modified UTF-8 to classic UTF-8 `
  - **C0199** · [Cod, linia 3366](src/core/android/SDL_android.c#L3366) · Motiv: Conversia modified UTF-8 versus UTF-8 poate altera textul; verificați caracterele afectate.

### `src/dialog/unix/SDL_portaldialog.c`

- [ ] Linia **537**: `     /* TODO: This should be registered before opening the portal, or the filter will not catch `
  - **C0229** · [Cod, linia 537](src/dialog/unix/SDL_portaldialog.c#L537) · Motiv: Ordinea înregistrării filtrului poate pierde răspunsul portalului; verificați finalizarea callback-ului.

### `src/gpu/d3d12/SDL_gpu_d3d12.c`

- [ ] Linia **1244**: ` // FIXME: This is purely to work around a presentation bug when recreating the device/command queue. `
  - **C0257** · [Cod, linia 1244](src/gpu/d3d12/SDL_gpu_d3d12.c#L1244) · Motiv: Workaround pentru prezentare; verificați scenariul de recreare și protecția existentă, nu îl eliminați automat.

- [ ] Linia **2674**: `     // FIXME: shouldn't have to assert here `
  - **C0260** · [Cod, linia 2674](src/gpu/d3d12/SDL_gpu_d3d12.c#L2674) · Motiv: Assert semnalat ca nejustificat; investigați precondițiile, nu presupuneți un crash.

- [ ] Linia **7694**: `     // FIXME: Should this happen before the inFlightFences stuff above? `
  - **C0266** · [Cod, linia 7694](src/gpu/d3d12/SDL_gpu_d3d12.c#L7694) · Motiv: Ordinea fence-urilor/reference counting poate afecta lifetime-ul resurselor GPU; audit și harness submit/release.

- [ ] Linia **7931**: `     // TODO: More reference counting `
  - **C0267** · [Cod, linia 7931](src/gpu/d3d12/SDL_gpu_d3d12.c#L7931) · Motiv: Ordinea fence-urilor/reference counting poate afecta lifetime-ul resurselor GPU; audit și harness submit/release.

### `src/gpu/metal/SDL_gpu_metal.m`

- [ ] Linia **1373**: `         samplerDesc.mipFilter = SDLToMetal_MipFilter[createinfo->mipmap_mode]; // FIXME: Is this right with non-mipmapped samplers? `
  - **C0275** · [Cod, linia 1373](src/gpu/metal/SDL_gpu_metal.m#L1373) · Motiv: Validitatea samplerelor sau a accesului simultan read/write trebuie stabilită prin contract și teste backend.

- [ ] Linia **4184**: ` // FIXME: Check simultaneous read-write support `
  - **C0280** · [Cod, linia 4184](src/gpu/metal/SDL_gpu_metal.m#L4184) · Motiv: Validitatea samplerelor sau a accesului simultan read/write trebuie stabilită prin contract și teste backend.

### `src/gpu/SDL_gpu.c`

- [ ] Linia **1069**: `                 // TODO: validate that format support blending? `
  - **C0282** · [Cod, linia 1069](src/gpu/SDL_gpu.c#L1069) · Motiv: Validări de utilizare/format lipsă conform marcajelor; verificați respingerea combinațiilor invalide.

- [ ] Linia **1093**: `             // TODO: validate that format supports belnding? This is only required on Metal. `
  - **C0283** · [Cod, linia 1093](src/gpu/SDL_gpu.c#L1093) · Motiv: Validări de utilizare/format lipsă conform marcajelor; verificați respingerea combinațiilor invalide.

- [ ] Linia **2484**: `         // TODO: validate buffer usage? `
  - **C0284** · [Cod, linia 2484](src/gpu/SDL_gpu.c#L2484) · Motiv: Validări de utilizare/format lipsă conform marcajelor; verificați respingerea combinațiilor invalide.

### `src/gpu/vulkan/SDL_gpu_vulkan.c`

- [ ] Linia **6685**: `     // FIXME: It is uncertain if drivers are able to load both byte orders. If `
  - **C0289** · [Cod, linia 6685](src/gpu/vulkan/SDL_gpu_vulkan.c#L6685) · Motiv: Compatibilitatea byte order la încărcare este incertă; verificare de rezultate corecte, fără presupuneri despre driver.

### `src/haptic/windows/SDL_dinputhaptic.c`

- [ ] Linia **294**: `     /* !!! FIXME: opening a haptic device here first will make an attempt to `
  - **C0307** · [Cod, linia 294](src/haptic/windows/SDL_dinputhaptic.c#L294) · Motiv: Același comentariu descrie deschiderea joystickului care eșuează după deschiderea exclusivă haptic; o singură problemă.

- [ ] Linia **295**: `        !!! FIXME:  SDL_OpenJoystick() that same device fail later, since we `
  - **C0308** · [Cod, linia 295](src/haptic/windows/SDL_dinputhaptic.c#L295) · Motiv: Același comentariu descrie deschiderea joystickului care eșuează după deschiderea exclusivă haptic; o singură problemă.

- [ ] Linia **296**: `        !!! FIXME:  have it open in exclusive mode. But this will allow `
  - **C0309** · [Cod, linia 296](src/haptic/windows/SDL_dinputhaptic.c#L296) · Motiv: Același comentariu descrie deschiderea joystickului care eșuează după deschiderea exclusivă haptic; o singură problemă.

- [ ] Linia **297**: `        !!! FIXME:  SDL_OpenJoystick() followed by SDL_OpenHapticFromJoystick() `
  - **C0310** · [Cod, linia 297](src/haptic/windows/SDL_dinputhaptic.c#L297) · Motiv: Același comentariu descrie deschiderea joystickului care eșuează după deschiderea exclusivă haptic; o singură problemă.

- [ ] Linia **298**: `        !!! FIXME:  to work, and that's probably the common case. Still, `
  - **C0311** · [Cod, linia 298](src/haptic/windows/SDL_dinputhaptic.c#L298) · Motiv: Același comentariu descrie deschiderea joystickului care eșuează după deschiderea exclusivă haptic; o singură problemă.

- [ ] Linia **299**: `        !!! FIXME:  ideally, We need to unify the opening code. */ `
  - **C0312** · [Cod, linia 299](src/haptic/windows/SDL_dinputhaptic.c#L299) · Motiv: Același comentariu descrie deschiderea joystickului care eșuează după deschiderea exclusivă haptic; o singură problemă.

### `src/haptic/windows/SDL_windowshaptic.c`

- [ ] Linia **247**: `         // !!! FIXME: (...is leaking on purpose a good idea?) - No, of course not. `
  - **C0314** · [Cod, linia 247](src/haptic/windows/SDL_windowshaptic.c#L247) · Motiv: Leak intenționat semnalat; verificați frecvența și ownership-ul înainte de modificarea eliberării.

### `src/io/io_uring/SDL_asyncio_liburing.c`

- [ ] Linia **386**: ``     // !!! FIXME: `unsigned` is likely smaller than requested_size's Uint64. If we overflow it, we could try submitting multiple SQEs ``
  - **C0336** · [Cod, linia 386](src/io/io_uring/SDL_asyncio_liburing.c#L386) · Motiv: Uint64 redus la unsigned: risc de I/O incomplet pentru cereri mari; continuările nu sunt probleme separate.

- [ ] Linia **387**: `     // !!! FIXME:  and make a note in the task that there are several in sequence. `
  - **C0337** · [Cod, linia 387](src/io/io_uring/SDL_asyncio_liburing.c#L387) · Motiv: Uint64 redus la unsigned: risc de I/O incomplet pentru cereri mari; continuările nu sunt probleme separate.

- [ ] Linia **412**: ``     // !!! FIXME: `unsigned` is likely smaller than requested_size's Uint64. If we overflow it, we could try submitting multiple SQEs ``
  - **C0338** · [Cod, linia 412](src/io/io_uring/SDL_asyncio_liburing.c#L412) · Motiv: Uint64 redus la unsigned: risc de I/O incomplet pentru cereri mari; continuările nu sunt probleme separate.

- [ ] Linia **413**: `     // !!! FIXME:  and make a note in the task that there are several in sequence. `
  - **C0339** · [Cod, linia 413](src/io/io_uring/SDL_asyncio_liburing.c#L413) · Motiv: Uint64 redus la unsigned: risc de I/O incomplet pentru cereri mari; continuările nu sunt probleme separate.

### `src/io/SDL_asyncio.c`

- [ ] Linia **237**: `         SDL_assert(async_close_task_was_queued);  // !!! FIXME: if this fails to queue the task, we're leaking resources! `
  - **C0340** · [Cod, linia 237](src/io/SDL_asyncio.c#L237) · Motiv: Eșecul punerii taskului close în coadă poate lăsa resurse neeliberate, conform comentariului.

- [ ] Linia **327**: `             // !!! FIXME: check if flen > address space, since it'll truncate and we'll just end up with an incomplete buffer or a crash. `
  - **C0341** · [Cod, linia 327](src/io/SDL_asyncio.c#L327) · Motiv: Comentariul menționează trunchiere, buffer incomplet sau crash pentru fișiere peste spațiul de adresare; nu pierdere de date demonstrată.

### `src/io/SDL_iostream.c`

- [ ] Linia **238**: ``             return 0;  // !!! FIXME: this should return the bytes read from any readahead we finished out before this (the `iodata->left > 0` code above). In that case, fail on the next read. ``
  - **C0343** · [Cod, linia 238](src/io/SDL_iostream.c#L238) · Motiv: Numărul de octeți raportat poate omite date deja citite; testați citirile parțiale și erorile.

- [ ] Linia **262**: ``             return 0;  // !!! FIXME: this should return the bytes read from any readahead we finished out before this (the `iodata->left > 0` code above). In that case, fail on the next read. ``
  - **C0344** · [Cod, linia 262](src/io/SDL_iostream.c#L262) · Motiv: Numărul de octeți raportat poate omite date deja citite; testați citirile parțiale și erorile.

### `src/io/windows/SDL_asyncio_windows_ioring.c`

- [ ] Linia **382**: `     // !!! FIXME: UINT32 smaller than requested_size's Uint64. If we overflow it, we could try submitting multiple SQEs `
  - **C0347** · [Cod, linia 382](src/io/windows/SDL_asyncio_windows_ioring.c#L382) · Motiv: Uint64 redus la UINT32: risc de I/O incomplet pentru cereri mari; verificați limitele și contractul.

- [ ] Linia **383**: `     // !!! FIXME:  and make a note in the task that there are several in sequence. `
  - **C0348** · [Cod, linia 383](src/io/windows/SDL_asyncio_windows_ioring.c#L383) · Motiv: Uint64 redus la UINT32: risc de I/O incomplet pentru cereri mari; verificați limitele și contractul.

- [ ] Linia **408**: `     // !!! FIXME: UINT32 smaller than requested_size's Uint64. If we overflow it, we could try submitting multiple SQEs `
  - **C0349** · [Cod, linia 408](src/io/windows/SDL_asyncio_windows_ioring.c#L408) · Motiv: Uint64 redus la UINT32: risc de I/O incomplet pentru cereri mari; verificați limitele și contractul.

- [ ] Linia **409**: `     // !!! FIXME:  and make a note in the task that there are several in sequence. `
  - **C0350** · [Cod, linia 409](src/io/windows/SDL_asyncio_windows_ioring.c#L409) · Motiv: Uint64 redus la UINT32: risc de I/O incomplet pentru cereri mari; verificați limitele și contractul.

### `src/joystick/hidapi/SDL_hidapijoystick.c`

- [ ] Linia **1480**: `         // FIXME: The device could be freed after this name is returned... `
  - **C0376** · [Cod, linia 1480](src/joystick/hidapi/SDL_hidapijoystick.c#L1480) · Motiv: Dispozitivul poate fi eliberat după returnarea name/path conform comentariului; investigați lifetime/use-after-free potențial.

- [ ] Linia **1494**: `         // FIXME: The device could be freed after this path is returned... `
  - **C0377** · [Cod, linia 1494](src/joystick/hidapi/SDL_hidapijoystick.c#L1494) · Motiv: Dispozitivul poate fi eliberat după returnarea name/path conform comentariului; investigați lifetime/use-after-free potențial.

### `src/render/direct3d11/SDL_render_d3d11.c`

- [ ] Linia **786**: `     // FIXME `
  - **C0405** · [Cod, linia 786](src/render/direct3d11/SDL_render_d3d11.c#L786) · Motiv: Contextul local returnează întotdeauna rotația IDENTITY; verificați randarea pe display-uri rotite.

### `src/render/direct3d12/SDL_render_d3d12.c`

- [ ] Linia **559**: `     // FIXME should we also clear currentSampler.ptr and currentRenderTargetView.ptr ? (and use D3D12_InvalidateCachedState() instead) `
  - **C0408** · [Cod, linia 559](src/render/direct3d12/SDL_render_d3d12.c#L559) · Motiv: Invalidarea stării cached poate fi incompletă; verificați reutilizarea descriptorilor, fără cauză stabilită.

- [ ] Linia **1166**: `     // FIXME `
  - **C0409** · [Cod, linia 1166](src/render/direct3d12/SDL_render_d3d12.c#L1166) · Motiv: Contextul local returnează întotdeauna rotația IDENTITY; verificați randarea pe display-uri rotite.

### `src/render/gpu/SDL_render_gpu.c`

- [ ] Linia **734**: `     // *** FIXME *** `
  - **C0413** · [Cod, linia 734](src/render/gpu/SDL_render_gpu.c#L734) · Motiv: Contextul local declară alegerea load_op incorectă în multe cazuri; testați contractul LOAD/CLEAR/DONT_CARE.

### `src/render/gpu/SDL_shaders_gpu.c`

- [ ] Linia **191**: `     // FIXME not sure if this is correct `
  - **C0417** · [Cod, linia 191](src/render/gpu/SDL_shaders_gpu.c#L191) · Motiv: Corectitudinea codului shader este pusă sub semnul întrebării; conformance înainte de fix.

### `src/render/metal/SDL_render_metal.m`

- [ ] Linia **1787**: `                     // !!! FIXME: have to commit, or an uncommitted but enqueued buffer will prevent the frame from finishing. `
  - **C0422** · [Cod, linia 1787](src/render/metal/SDL_render_metal.m#L1787) · Motiv: Condiție descrisă ca împiedicând finalizarea frame-ului; verificați protecția existentă și ordinea commit-urilor.

- [ ] Linia **2262**: `         // !!! FIXME: error checking on all of this. `
  - **C0423** · [Cod, linia 2262](src/render/metal/SDL_render_metal.m#L2262) · Motiv: Verificări de erori/inițializare drawable semnalate; audit de cleanup și conformance pentru primele frame-uri.

- [ ] Linia **2377**: `         // !!! FIXME: force more clears here so all the drawables are sane to start, and our static buffers are definitely flushed. `
  - **C0424** · [Cod, linia 2377](src/render/metal/SDL_render_metal.m#L2377) · Motiv: Verificări de erori/inițializare drawable semnalate; audit de cleanup și conformance pentru primele frame-uri.

### `src/render/opengl/SDL_render_gl.c`

- [ ] Linia **963**: `     // TODO: check if texture pixel format allows this operation `
  - **C0425** · [Cod, linia 963](src/render/opengl/SDL_render_gl.c#L963) · Motiv: Validitatea operației pentru formatul texturii necesită verificare.

### `src/render/ps2/SDL_render_ps2.c`

- [ ] Linia **515**: `             // FIXME: We need to update the clip rect too, see https://github.com/libsdl-org/SDL/issues/9094 `
  - **C0435** · [Cod, linia 515](src/render/ps2/SDL_render_ps2.c#L515) · Motiv: Actualizarea clip rect este semnalată ca lipsă; scene deterministe pentru clipping.

### `src/render/psp/SDL_render_psp.c`

- [ ] Linia **1053**: `             // FIXME SDL_BLENDMODE_MUL is simplified, and dstA is in fact un-changed. `
  - **C0436** · [Cod, linia 1053](src/render/psp/SDL_render_psp.c#L1053) · Motiv: Comentariile descriu alpha simplificat și viewport fără efect; verificați rezultatele vizuale.

- [ ] Linia **1125**: `         /* FIXME: Find a genuine way to make viewport work (right now calling these functions here give no effect) */ `
  - **C0437** · [Cod, linia 1125](src/render/psp/SDL_render_psp.c#L1125) · Motiv: Comentariile descriu alpha simplificat și viewport fără efect; verificați rezultatele vizuale.

### `src/render/software/SDL_blendline.c`

- [ ] Linia **936**: `     // FIXME: We don't actually want to clip, as it may change line slope `
  - **C0441** · [Cod, linia 936](src/render/software/SDL_blendline.c#L936) · Motiv: Clipping-ul poate schimba panta liniei; verificare rasterizare, aceeași problemă în două locuri.

- [ ] Linia **969**: `         // FIXME: We don't actually want to clip, as it may change line slope `
  - **C0442** · [Cod, linia 969](src/render/software/SDL_blendline.c#L969) · Motiv: Clipping-ul poate schimba panta liniei; verificare rasterizare, aceeași problemă în două locuri.

### `src/render/software/SDL_drawline.c`

- [ ] Linia **150**: `     // FIXME: We don't actually want to clip, as it may change line slope `
  - **C0444** · [Cod, linia 150](src/render/software/SDL_drawline.c#L150) · Motiv: Clipping-ul poate schimba panta liniei; verificare rasterizare, aceeași problemă în două locuri.

- [ ] Linia **183**: `         // FIXME: We don't actually want to clip, as it may change line slope `
  - **C0445** · [Cod, linia 183](src/render/software/SDL_drawline.c#L183) · Motiv: Clipping-ul poate schimba panta liniei; verificare rasterizare, aceeași problemă în două locuri.

### `src/stdlib/SDL_getenv.c`

- [ ] Linia **102**: `     // Don't fail if we can't create a mutex (e.g. on a single-thread environment)  // !!! FIXME: single-threaded environments should still return a non-NULL, do-nothing object here. Check for failure! `
  - **C0458** · [Cod, linia 102](src/stdlib/SDL_getenv.c#L102) · Motiv: Eșecul creării mutexului poate fi ignorat; verificați multithreading și alocarea eșuată.

### `src/video/haiku/SDL_bmodes.cc`

- [ ] Linia **252**: `         // FIXME: Apparently there are errors with colorspace changes `
  - **C0519** · [Cod, linia 252](src/video/haiku/SDL_bmodes.cc#L252) · Motiv: Comentariul raportează erori la schimbarea colorspace; reproduceți pe Haiku.

### `src/video/kmsdrm/SDL_kmsdrmmouse.c`

- [ ] Linia **35**: ` // !!! FIXME: atomic cursors are broken right now. `
  - **C0539** · [Cod, linia 35](src/video/kmsdrm/SDL_kmsdrmmouse.c#L35) · Motiv: Marcajul declară cursori atomici nefuncționali; verificați dacă această cale este activă și reproduceți.

### `src/video/miniz.h`

- [ ] Linia **1452**: ` // TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never `
  - **C0556** · [Cod, linia 1452](src/video/miniz.h#L1452) · Motiv: Marcaj despre input epuizat și tentativa de citire dincolo de buffer; revizie parser/date trunchiate, fără vulnerabilitate confirmată.

### `src/video/SDL_blit.h`

- [ ] Linia **338**: ` // FIXME: Should we rescale alpha into 0..255 here? `
  - **C0564** · [Cod, linia 338](src/video/SDL_blit.h#L338) · Motiv: Scalarea/conversia alpha este pusă sub semnul întrebării sau declarată incorectă; verificare numerică/vizuală.

- [ ] Linia **444**: ` // FIXME: this isn't correct, especially for Alpha (maximum != 255) `
  - **C0565** · [Cod, linia 444](src/video/SDL_blit.h#L444) · Motiv: Scalarea/conversia alpha este pusă sub semnul întrebării sau declarată incorectă; verificare numerică/vizuală.

### `src/video/SDL_video.c`

- [ ] Linia **3651**: `                 /* !!! FIXME: if this failed halfway (made renderer, failed to make texture, etc), `
  - **C0574** · [Cod, linia 3651](src/video/SDL_video.c#L3651) · Motiv: Cleanup după inițializare parțială și selecție framebuffer per-window; două comentarii multilinie despre fallback, nu șapte buguri.

- [ ] Linia **3652**: `                    !!! FIXME:  we probably need to clean this up so it doesn't interfere with `
  - **C0575** · [Cod, linia 3652](src/video/SDL_video.c#L3652) · Motiv: Cleanup după inițializare parțială și selecție framebuffer per-window; două comentarii multilinie despre fallback, nu șapte buguri.

- [ ] Linia **3653**: `                    !!! FIXME:  a software fallback at the system level (can we blit to an `
  - **C0576** · [Cod, linia 3653](src/video/SDL_video.c#L3653) · Motiv: Cleanup după inițializare parțială și selecție framebuffer per-window; două comentarii multilinie despre fallback, nu șapte buguri.

- [ ] Linia **3654**: `                    !!! FIXME:  OpenGL window? etc). */ `
  - **C0577** · [Cod, linia 3654](src/video/SDL_video.c#L3654) · Motiv: Cleanup după inițializare parțială și selecție framebuffer per-window; două comentarii multilinie despre fallback, nu șapte buguri.

- [ ] Linia **3657**: `                 /* !!! FIXME:  maybe we shouldn't override these but check if we used a texture `
  - **C0578** · [Cod, linia 3657](src/video/SDL_video.c#L3657) · Motiv: Cleanup după inițializare parțială și selecție framebuffer per-window; două comentarii multilinie despre fallback, nu șapte buguri.

- [ ] Linia **3658**: `                    !!! FIXME:  framebuffer at the right places; is it feasible we could have an `
  - **C0579** · [Cod, linia 3658](src/video/SDL_video.c#L3658) · Motiv: Cleanup după inițializare parțială și selecție framebuffer per-window; două comentarii multilinie despre fallback, nu șapte buguri.

- [ ] Linia **3659**: `                    !!! FIXME:  accelerated OpenGL window and a second ends up in software? */ `
  - **C0580** · [Cod, linia 3659](src/video/SDL_video.c#L3659) · Motiv: Cleanup după inițializare parțială și selecție framebuffer per-window; două comentarii multilinie despre fallback, nu șapte buguri.

### `src/video/windows/SDL_windowswindow.c`

- [ ] Linia **759**: `     // FIXME: does not work on all hardware configurations with different renders (i.e. hybrid GPUs) `
  - **C0635** · [Cod, linia 759](src/video/windows/SDL_windowswindow.c#L759) · Motiv: Configurații hybrid GPU descrise ca nefuncționale; scenariu real multi-adapter necesar.

### `test/testautomation_video.c`

- [ ] Linia **2114**: `      * FIXME: Maximizing Win32 borderless windows is broken, so this always fails. `
  - **C0674** · [Cod, linia 2114](test/testautomation_video.c#L2114) · Motiv: Testul documentează maximizare Win32 borderless defectă; reproduceți înainte de atribuirea ownership-ului.

## MEDIUM

### `android-project/app/src/main/java/org/libsdl/app/HIDDeviceBLESteamController.java`

- [ ] Linia **432**: `             boolean result = op.finish(); // TODO: Maybe in main thread as well? `
  - **C0001** · [Cod, linia 432](android-project/app/src/main/java/org/libsdl/app/HIDDeviceBLESteamController.java#L432) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `android-project/app/src/main/java/org/libsdl/app/SDLActivity.java`

- [ ] Linia **774**: `             // TODO: Detect the file MIME type and pass the filter value accordingly. `
  - **C0002** · [Cod, linia 774](android-project/app/src/main/java/org/libsdl/app/SDLActivity.java#L774) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **862**: `                     // FIXME: Why aren't we enabling sensor input at start? `
  - **C0003** · [Cod, linia 862](android-project/app/src/main/java/org/libsdl/app/SDLActivity.java#L862) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1640**: `         // TODO set values from "flags" to messagebox dialog `
  - **C0004** · [Cod, linia 1640](android-project/app/src/main/java/org/libsdl/app/SDLActivity.java#L1640) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1723**: `                 // TODO set color for border of messagebox button `
  - **C0005** · [Cod, linia 1723](android-project/app/src/main/java/org/libsdl/app/SDLActivity.java#L1723) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1736**: `                 // TODO set color for selected messagebox button `
  - **C0006** · [Cod, linia 1736](android-project/app/src/main/java/org/libsdl/app/SDLActivity.java#L1736) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `android-project/app/src/main/java/org/libsdl/app/SDLDummyEdit.java`

- [ ] Linia **42**: `         // FIXME: Discussion at http://bugzilla.libsdl.org/show_bug.cgi?id=1639 `
  - **C0007** · [Cod, linia 42](android-project/app/src/main/java/org/libsdl/app/SDLDummyEdit.java#L42) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **43**: `         // FIXME: This is not a 100% effective solution to the problem of detecting if the keyboard is showing or not `
  - **C0008** · [Cod, linia 43](android-project/app/src/main/java/org/libsdl/app/SDLDummyEdit.java#L43) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **44**: `         // FIXME: A more effective solution would be to assume our Layout to be RelativeLayout or LinearLayout `
  - **C0009** · [Cod, linia 44](android-project/app/src/main/java/org/libsdl/app/SDLDummyEdit.java#L44) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **45**: `         // FIXME: And determine the keyboard presence doing this: http://stackoverflow.com/questions/2150078/how-to-check-visibility-of-software-keyboard-in-android `
  - **C0010** · [Cod, linia 45](android-project/app/src/main/java/org/libsdl/app/SDLDummyEdit.java#L45) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **46**: `         // FIXME: An even more effective way would be if Android provided this out of the box, but where would the fun be in that :) `
  - **C0011** · [Cod, linia 46](android-project/app/src/main/java/org/libsdl/app/SDLDummyEdit.java#L46) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `android-project/app/src/main/java/org/libsdl/app/SDLInputConnection.java`

- [ ] Linia **103**: `         /* FIXME: This doesn't handle graphemes, like '🌬️' */ `
  - **C0012** · [Cod, linia 103](android-project/app/src/main/java/org/libsdl/app/SDLInputConnection.java#L103) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `android-project/app/src/main/java/org/libsdl/app/SDLSurface.java`

- [ ] Linia **329**: `         // TODO: This uses getDefaultSensor - what if we have >1 accels? `
  - **C0013** · [Cod, linia 329](android-project/app/src/main/java/org/libsdl/app/SDLSurface.java#L329) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **342**: `         // TODO `
  - **C0014** · [Cod, linia 342](android-project/app/src/main/java/org/libsdl/app/SDLSurface.java#L342) · Motiv: Callback onAccuracyChanged gol în contextul local; clarificați comportamentul dorit.

### `build-scripts/build-release.py`

- [ ] Linia **528**: `         # FIXME: find out why some files are not shown in "git log" `
  - **C0015** · [Cod, linia 528](build-scripts/build-release.py#L528) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `build-scripts/makecasefoldhashtable.pl`

- [ ] Linia **181**: `             die("Uhoh, a codepoint > 0xFFFF that folds to multiple codepoints! Fixme.") if defined($map2); `
  - **C0017** · [Cod, linia 181](build-scripts/makecasefoldhashtable.pl#L181) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `build-scripts/update-version.sh`

- [ ] Linia **32**: ` # !!! FIXME: This first one is a kinda scary search/replace that might fail later if another X.Y.Z version is added to the file. `
  - **C0035** · [Cod, linia 32](build-scripts/update-version.sh#L32) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `cmake/GetGitRevisionDescription.cmake`

- [ ] Linia **209**: `     # TODO sanitize `
  - **C0061** · [Cod, linia 209](cmake/GetGitRevisionDescription.cmake#L209) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `cmake/sdlchecks.cmake`

- [ ] Linia **16**: `   # FIXME: fail FindLibraryAndSONAME when library is not shared. `
  - **C0063** · [Cod, linia 16](cmake/sdlchecks.cmake#L16) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **124**: `         #FIXME: remove this line and property generate sdl3.pc `
  - **C0064** · [Cod, linia 124](cmake/sdlchecks.cmake#L124) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1240**: `     #FIXME: properly add usb libs with pkg-config or whatever `
  - **C0066** · [Cod, linia 1240](cmake/sdlchecks.cmake#L1240) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `cmake/test/CMakeLists.txt`

- [ ] Linia **8**: ` # FIXME: how to target ios/tvos with Swift? `
  - **C0068** · [Cod, linia 8](cmake/test/CMakeLists.txt#L8) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `CMakeLists.txt`

- [ ] Linia **575**: `     # FIXME `
  - **C0069** · [Cod, linia 575](CMakeLists.txt#L575) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **669**: `     #FIXME: originally this if had an additional "AND NOT (USE_CLANG AND WINDOWS)" `
  - **C0070** · [Cod, linia 669](CMakeLists.txt#L669) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **910**: `     # TODO: Those all seem to be quite GCC specific - needs to be `
  - **C0071** · [Cod, linia 910](CMakeLists.txt#L910) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1042**: ` # TODO: Can't deactivate on FreeBSD? w/o LIBC, SDL_stdinc.h can't define anything. `
  - **C0072** · [Cod, linia 1042](CMakeLists.txt#L1042) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1469**: `   set(SDL_FSOPS_POSIX 1)  # !!! FIXME: this might need something else for .apk data? `
  - **C0074** · [Cod, linia 1469](CMakeLists.txt#L1469) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1557**: `     # FIXME failing dlopen https://github.com/android-ndk/ndk/issues/929 `
  - **C0075** · [Cod, linia 1557](CMakeLists.txt#L1557) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2232**: `     if(SDL_CPU_ARM32)  # !!! FIXME: this should probably check if we're !(x86 or x86-64) instead of arm. `
  - **C0076** · [Cod, linia 2232](CMakeLists.txt#L2232) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2494**: `   # TODO: rework this all for proper macOS, iOS and Darwin support `
  - **C0077** · [Cod, linia 2494](CMakeLists.txt#L2494) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2645**: `   # TODO: SDL_STORAGE_ICLOUD `
  - **C0082** · [Cod, linia 2645](CMakeLists.txt#L2645) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **3276**: `   # !!! FIXME: do we need a FSops implementation for this? `
  - **C0084** · [Cod, linia 3276](CMakeLists.txt#L3276) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `examples/template.html`

- [ ] Linia **281**: `         // TODO: do not warn on ok events like simulating an infinite loop or exitStatus `
  - **C0089** · [Cod, linia 281](examples/template.html#L281) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `include/build_config/SDL_build_config_wingdk.h`

- [ ] Linia **229**: ` /* Enable the camera driver (src/camera/dummy/\*.c) */  /* !!! FIXME */ `
  - **C0090** · [Cod, linia 229](include/build_config/SDL_build_config_wingdk.h#L229) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `include/build_config/SDL_build_config_xbox.h`

- [ ] Linia **212**: ` /* Disable IME as not supported yet (TODO: Xbox IME?) */ `
  - **C0091** · [Cod, linia 212](include/build_config/SDL_build_config_xbox.h#L212) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `include/SDL3/SDL_begin_code.h`

- [ ] Linia **511**: ` /** FIXME `
  - **C0093** · [Cod, linia 511](include/SDL3/SDL_begin_code.h#L511) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `include/SDL3/SDL_gpu.h`

- [ ] Linia **682**: `  * FIXME: Check universal support for 32-bit component formats FIXME: Check `
  - **C0094** · [Cod, linia 682](include/SDL3/SDL_gpu.h#L682) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `include/SDL3/SDL_haptic.h`

- [ ] Linia **130**: ` /* FIXME: `
  - **C0095** · [Cod, linia 130](include/SDL3/SDL_haptic.h#L130) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `include/SDL3/SDL_stdinc.h`

- [ ] Linia **1201**: ` /* TODO: include/SDL_stdinc.h:390: error: size of array 'SDL_dummy_enum' is negative */ `
  - **C0096** · [Cod, linia 1201](include/SDL3/SDL_stdinc.h#L1201) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/atomic/SDL_spinlock.c`

- [ ] Linia **153**: `     // FIXME: Should we have an eventual timeout? `
  - **C0098** · [Cod, linia 153](src/atomic/SDL_spinlock.c#L153) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **159**: `             // !!! FIXME: this doesn't definitely give up the current timeslice, it does different things on various platforms. `
  - **C0099** · [Cod, linia 159](src/atomic/SDL_spinlock.c#L159) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/aaudio/SDL_aaudio.c`

- [ ] Linia **273**: `             // !!! FIXME: do we have to wait for the state to change to make sure all buffered audio has played, or will close do this (or will the system do this after the close)? `
  - **C0100** · [Cod, linia 273](src/audio/aaudio/SDL_aaudio.c#L273) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **301**: `             // !!! FIXME: I _think_ this is okay with the current set of usages we support, but the docs `
  - **C0102** · [Cod, linia 301](src/audio/aaudio/SDL_aaudio.c#L301) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **302**: `             // !!! FIXME:  say you need to dip down into Java to call android.app.Activity.setVolumeControlStream(usage) `
  - **C0103** · [Cod, linia 302](src/audio/aaudio/SDL_aaudio.c#L302) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **303**: `             // !!! FIXME:  so the physical volume buttons control this stream, but that might be more for special cases `
  - **C0104** · [Cod, linia 303](src/audio/aaudio/SDL_aaudio.c#L303) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **304**: `             // !!! FIXME:  like notification sounds, etc, and it's possible you _don't_ want to override this for those `
  - **C0105** · [Cod, linia 304](src/audio/aaudio/SDL_aaudio.c#L304) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **305**: `             // !!! FIXME:  special cases, too! We'll revisit if there are bug reports. `
  - **C0106** · [Cod, linia 305](src/audio/aaudio/SDL_aaudio.c#L305) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **446**: ` // !!! FIXME: make this non-blocking! `
  - **C0107** · [Cod, linia 446](src/audio/aaudio/SDL_aaudio.c#L446) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **461**: `         // !!! FIXME: make this non-blocking! `
  - **C0108** · [Cod, linia 461](src/audio/aaudio/SDL_aaudio.c#L461) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/alsa/SDL_alsa_audio.c`

- [ ] Linia **330**: ` // TODO: Figure out the "right"(TM) way. For the moment we presume that if a system is using a `
  - **C0110** · [Cod, linia 330](src/audio/alsa/SDL_alsa_audio.c#L330) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/coreaudio/SDL_coreaudio.m`

- [ ] Linia **846**: `         // !!! FIXME: should we use AudioQueueEnqueueBufferWithParameters and specify all frames be "trimmed" so these are immediately ready to refill with SDL callback data? `
  - **C0113** · [Cod, linia 846](src/audio/coreaudio/SDL_coreaudio.m#L846) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/haiku/SDL_haikuaudio.cc`

- [ ] Linia **119**: `     format.channel_count = device->spec.channels;        // !!! FIXME: support > 2? `
  - **C0116** · [Cod, linia 119](src/audio/haiku/SDL_haikuaudio.cc#L119) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/openslES/SDL_openslES.c`

- [ ] Linia **229**: ` // !!! FIXME: make this non-blocking! `
  - **C0120** · [Cod, linia 229](src/audio/openslES/SDL_openslES.c#L229) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **248**: `     // !!! FIXME: make this non-blocking! `
  - **C0121** · [Cod, linia 248](src/audio/openslES/SDL_openslES.c#L248) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/qnx/SDL_qsa_audio.c`

- [ ] Linia **22**: ` // !!! FIXME: can this target support hotplugging? `
  - **C0122** · [Cod, linia 22](src/audio/qnx/SDL_qsa_audio.c#L22) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **60**: ` // !!! FIXME: does this need to be here? Does the SDL version not work? `
  - **C0123** · [Cod, linia 60](src/audio/qnx/SDL_qsa_audio.c#L60) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **103**: `         device->hidden->timeout_on_wait = true;  // !!! FIXME: Should we just disconnect the device in this case? `
  - **C0124** · [Cod, linia 103](src/audio/qnx/SDL_qsa_audio.c#L103) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **128**: `                     return true;  // oh well, try again next time.  !!! FIXME: Should we just disconnect the device in this case? `
  - **C0125** · [Cod, linia 128](src/audio/qnx/SDL_qsa_audio.c#L128) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **196**: `         return SDL_SetError("SDL recording support isn't available on QNX atm"); // !!! FIXME: most of this code has support for recording devices, but there's no RecordDevice, etc functions. Fill them in! `
  - **C0126** · [Cod, linia 196](src/audio/qnx/SDL_qsa_audio.c#L196) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **356**: `                     #if 0  // !!! FIXME: most of this code has support for recording devices, but there's no RecordDevice, etc functions. Fill them in! `
  - **C0127** · [Cod, linia 356](src/audio/qnx/SDL_qsa_audio.c#L356) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **382**: `                         // !!! FIXME: I'm assuming each of these values are way less than 0xFFFF. Fix this if not. `
  - **C0128** · [Cod, linia 382](src/audio/qnx/SDL_qsa_audio.c#L382) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **407**: `         // !!! FIXME: I'm assuming each of these values are way less than 0xFFFF. Fix this if not. `
  - **C0129** · [Cod, linia 407](src/audio/qnx/SDL_qsa_audio.c#L407) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **416**: `         // !!! FIXME: I'm assuming each of these values are way less than 0xFFFF. Fix this if not. `
  - **C0130** · [Cod, linia 416](src/audio/qnx/SDL_qsa_audio.c#L416) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **440**: `     // !!! FIXME: most of this code has support for recording devices, but there's no RecordDevice, etc functions. Fill them in! `
  - **C0131** · [Cod, linia 440](src/audio/qnx/SDL_qsa_audio.c#L440) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/SDL_audio.c`

- [ ] Linia **2380**: `     if (!new_default_device) {  // !!! FIXME: what should we do in this case? Maybe all devices are lost, so there _isn't_ a default? `
  - **C0140** · [Cod, linia 2380](src/audio/SDL_audio.c#L2380) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/SDL_audiocvt.c`

- [ ] Linia **157**: `     bool has_null_mappings = false;  // !!! FIXME: calculate this when setting the channel map instead. `
  - **C0143** · [Cod, linia 157](src/audio/SDL_audiocvt.c#L157) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **186**: `             Uint##bits *tmp = (Uint##bits *) SDL_small_alloc(int, channels, &isstack); /* !!! FIXME: allocate this when setting the channel map instead. */ \ `
  - **C0144** · [Cod, linia 186](src/audio/SDL_audiocvt.c#L186) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **969**: `         // !!! FIXME: it would be possible to do this really well in SIMD for stereo data, using unpack (intel) or zip (arm) instructions, etc. `
  - **C0145** · [Cod, linia 969](src/audio/SDL_audiocvt.c#L969) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/SDL_audioresample.c`

- [ ] Linia **30**: ` // TODO: Support changing this at runtime? `
  - **C0147** · [Cod, linia 30](src/audio/SDL_audioresample.c#L30) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/SDL_audiotypecvt.c`

- [ ] Linia **488**: ` // FIXME: SDL doesn't have SSSE3 detection, so use the next one up `
  - **C0148** · [Cod, linia 488](src/audio/SDL_audiotypecvt.c#L488) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/SDL_mixer.c`

- [ ] Linia **85**: ` // !!! FIXME: This needs some SIMD magic. `
  - **C0149** · [Cod, linia 85](src/audio/SDL_mixer.c#L85) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **86**: ` // !!! FIXME: Add fast-path for volume = 1 `
  - **C0150** · [Cod, linia 86](src/audio/SDL_mixer.c#L86) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **87**: ` // !!! FIXME: Use larger scales for 16-bit/32-bit integers `
  - **C0151** · [Cod, linia 87](src/audio/SDL_mixer.c#L87) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **285**: `     default: // If this happens... FIXME! `
  - **C0152** · [Cod, linia 285](src/audio/SDL_mixer.c#L285) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/SDL_sysaudio.h`

- [ ] Linia **170**: `     bool OnlyHasDefaultRecordingDevice;   // !!! FIXME: is there ever a time where you'd have a default playback and not a default recording (or vice versa)? `
  - **C0156** · [Cod, linia 170](src/audio/SDL_sysaudio.h#L170) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/vita/SDL_vitaaudio.c`

- [ ] Linia **140**: `     // !!! FIXME: we might just need to sleep roughly as long as playback buffers take to process, based on sample rate, etc. `
  - **C0160** · [Cod, linia 140](src/audio/vita/SDL_vitaaudio.c#L140) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/audio/wasapi/SDL_wasapi.c`

- [ ] Linia **675**: `     /* !!! FIXME: we could request an exclusive mode stream, which is lower latency; `
  - **C0162** · [Cod, linia 675](src/audio/wasapi/SDL_wasapi.c#L675) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/camera/android/SDL_camera_android.c`

- [ ] Linia **323**: `     // !!! FIXME: this currently copies the data to the surface (see FIXME about non-contiguous planar surfaces, but in theory we could just keep this locked until ReleaseFrame... `
  - **C0163** · [Cod, linia 323](src/camera/android/SDL_camera_android.c#L323) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **390**: `     // !!! FIXME: this currently copies the data to the surface, but in theory we could just keep the AImage until ReleaseFrame... `
  - **C0164** · [Cod, linia 390](src/camera/android/SDL_camera_android.c#L390) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **579**: ` #if 0  // !!! FIXME: for now, we'll just let this fail if it is going to fail, without checking for this `
  - **C0165** · [Cod, linia 579](src/camera/android/SDL_camera_android.c#L579) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **689**: ` #if 0 // !!! FIXME: these all come out with 0 durations on my test phone.  :( `
  - **C0166** · [Cod, linia 689](src/camera/android/SDL_camera_android.c#L689) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/camera/coremedia/SDL_camera_coremedia.m`

- [ ] Linia **188**: `     // !!! FIXME: this currently copies the data to the surface (see FIXME about non-contiguous planar surfaces, but in theory we could just keep this locked until ReleaseFrame... `
  - **C0168** · [Cod, linia 188](src/camera/coremedia/SDL_camera_coremedia.m#L188) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **205**: `         // !!! FIXME: we have an open issue in SDL3 to allow SDL_Surface to support non-contiguous planar data, but we don't have it yet. `
  - **C0169** · [Cod, linia 205](src/camera/coremedia/SDL_camera_coremedia.m#L205) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **269**: `     // !!! FIXME: this currently copies the data to the surface, but in theory we could just keep this locked until ReleaseFrame... `
  - **C0170** · [Cod, linia 269](src/camera/coremedia/SDL_camera_coremedia.m#L269) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **484**: ``     [session startRunning];  // !!! FIXME: docs say this can block while camera warms up and shouldn't be done on main thread. Maybe push through `queue`? ``
  - **C0171** · [Cod, linia 484](src/camera/coremedia/SDL_camera_coremedia.m#L484) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **591**: `         // !!! FIXME: this can use Key Value Observation to get hotplug events. `
  - **C0172** · [Cod, linia 591](src/camera/coremedia/SDL_camera_coremedia.m#L591) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **595**: `         // !!! FIXME: this can use AVCaptureDeviceWasConnectedNotification and AVCaptureDeviceWasDisconnectedNotification with NSNotificationCenter to get hotplug events. `
  - **C0173** · [Cod, linia 595](src/camera/coremedia/SDL_camera_coremedia.m#L595) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **605**: `     // !!! FIXME: disable hotplug. `
  - **C0174** · [Cod, linia 605](src/camera/coremedia/SDL_camera_coremedia.m#L605) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/camera/emscripten/SDL_camera_emscripten.c`

- [ ] Linia **150**: `         function grabNextCameraFrame() {  // !!! FIXME: this (currently) runs as a requestAnimationFrame callback, for lack of a better option. `
  - **C0175** · [Cod, linia 150](src/camera/emscripten/SDL_camera_emscripten.c#L150) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **168**: `             requestAnimationFrame(grabNextCameraFrame);  // run this function again at the display framerate.  (!!! FIXME: would this be better as requestIdleCallback?) `
  - **C0176** · [Cod, linia 168](src/camera/emscripten/SDL_camera_emscripten.c#L168) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/camera/mediafoundation/SDL_camera_mediafoundation.c`

- [ ] Linia **776**: `     // !!! FIXME: do we actually have to find the media type object in the source reader or can we just roll our own like this? `
  - **C0178** · [Cod, linia 776](src/camera/mediafoundation/SDL_camera_mediafoundation.c#L776) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1022**: `     // !!! FIXME: use CM_Register_Notification (Win8+) to get device notifications. `
  - **C0179** · [Cod, linia 1022](src/camera/mediafoundation/SDL_camera_mediafoundation.c#L1022) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1023**: `     // !!! FIXME: Earlier versions can use RegisterDeviceNotification, but I'm not bothering: no hotplug for you! `
  - **C0180** · [Cod, linia 1023](src/camera/mediafoundation/SDL_camera_mediafoundation.c#L1023) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/camera/SDL_camera.c`

- [ ] Linia **124**: `         // !!! FIXME: this is bad for several reasons (uses double, could be precalculated, doesn't track elapsed time). `
  - **C0182** · [Cod, linia 124](src/camera/SDL_camera.c#L124) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **802**: `     // TODO `
  - **C0188** · [Cod, linia 802](src/camera/SDL_camera.c#L802) · Motiv: Contextul local indică setarea priorității threadului camerei Android comentată.

- [ ] Linia **910**: `                 SDL_StretchSurface(srcsurf, NULL, dstsurf, NULL, SDL_SCALEMODE_NEAREST);  // !!! FIXME: linear scale? letterboxing? `
  - **C0189** · [Cod, linia 910](src/camera/SDL_camera.c#L910) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **921**: `                 SDL_StretchSurface(srcsurf, NULL, output_surface, NULL, SDL_SCALEMODE_NEAREST);  // !!! FIXME: linear scale? letterboxing? `
  - **C0190** · [Cod, linia 921](src/camera/SDL_camera.c#L921) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/camera/v4l2/SDL_camera_v4l2.c`

- [ ] Linia **288**: `                 // !!! FIXME: disconnect the device. `
  - **C0192** · [Cod, linia 288](src/camera/v4l2/SDL_camera_v4l2.c#L288) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **304**: `                 // !!! FIXME: disconnect the device. `
  - **C0193** · [Cod, linia 304](src/camera/v4l2/SDL_camera_v4l2.c#L304) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **703**: `             // !!! FIXME: should we step by the numerator...? `
  - **C0194** · [Cod, linia 703](src/camera/v4l2/SDL_camera_v4l2.c#L703) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **717**: `             // FIXME: The current API does not enable exposing continuous ranges, so for now let's expose some common values that are within the range `
  - **C0195** · [Cod, linia 717](src/camera/v4l2/SDL_camera_v4l2.c#L717) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/core/android/SDL_android.c`

- [ ] Linia **1495**: `     // TODO: compute new mime types `
  - **C0196** · [Cod, linia 1495](src/core/android/SDL_android.c#L1495) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1790**: `     *default_playback = *default_recording = NULL;  // !!! FIXME: how do you decide the default device id? `
  - **C0197** · [Cod, linia 1790](src/core/android/SDL_android.c#L1790) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/core/haiku/SDL_BApp.h`

- [ ] Linia **66**: `     BAPP_RESTORE, // TODO: IMPLEMENT! `
  - **C0200** · [Cod, linia 66](src/core/haiku/SDL_BApp.h#L66) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **162**: `             // TODO: Handle screen resize or workspace change `
  - **C0201** · [Cod, linia 162](src/core/haiku/SDL_BApp.h#L162) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **188**: `         // TODO: error handling `
  - **C0202** · [Cod, linia 188](src/core/haiku/SDL_BApp.h#L188) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/core/linux/SDL_evdev_capabilities.c`

- [ ] Linia **106**: `             /* TODO: better determining between touchscreen and multitouch touchpad, `
  - **C0204** · [Cod, linia 106](src/core/linux/SDL_evdev_capabilities.c#L106) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/core/linux/SDL_evdev.c`

- [ ] Linia **79**: `     // TODO: use this for every device, not just touchscreen `
  - **C0205** · [Cod, linia 79](src/core/linux/SDL_evdev.c#L79) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **82**: `     /* TODO: expand on this to have data for every possible class (mouse, `
  - **C0206** · [Cod, linia 82](src/core/linux/SDL_evdev.c#L82) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **215**: `                 // TODO: Scan the devices manually, like a caveman `
  - **C0207** · [Cod, linia 215](src/core/linux/SDL_evdev.c#L215) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **387**: `                         if (!item->is_touchscreen) { // FIXME: temp hack `
  - **C0208** · [Cod, linia 387](src/core/linux/SDL_evdev.c#L387) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **393**: `                         if (!item->is_touchscreen) { // FIXME: temp hack `
  - **C0209** · [Cod, linia 393](src/core/linux/SDL_evdev.c#L393) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **404**: `                         if (!item->is_touchscreen) { // FIXME: temp hack `
  - **C0210** · [Cod, linia 404](src/core/linux/SDL_evdev.c#L404) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **413**: `                         if (!item->is_touchscreen) { // FIXME: temp hack `
  - **C0211** · [Cod, linia 413](src/core/linux/SDL_evdev.c#L413) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **422**: `                         if (!item->is_touchscreen) { // FIXME: temp hack `
  - **C0212** · [Cod, linia 422](src/core/linux/SDL_evdev.c#L422) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **527**: `                         if (!item->is_touchscreen) { // FIXME: temp hack `
  - **C0213** · [Cod, linia 527](src/core/linux/SDL_evdev.c#L527) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **545**: `                             /* FIXME: the touch's window shouldn't be null, but `
  - **C0214** · [Cod, linia 545](src/core/linux/SDL_evdev.c#L545) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **794**: `     // TODO: sync devices other than touchscreen `
  - **C0215** · [Cod, linia 794](src/core/linux/SDL_evdev.c#L794) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/core/linux/SDL_fcitx.c`

- [ ] Linia **229**: `         // FIXME, turn off native candidate rendering `
  - **C0217** · [Cod, linia 229](src/core/linux/SDL_fcitx.c#L229) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/core/linux/SDL_ibus.c`

- [ ] Linia **418**: `             // FIXME, turn off native candidate rendering `
  - **C0218** · [Cod, linia 418](src/core/linux/SDL_ibus.c#L418) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **636**: `     // !!! FIXME: should we close(inotify_fd) here? `
  - **C0219** · [Cod, linia 636](src/core/linux/SDL_ibus.c#L636) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/core/openbsd/SDL_wscons_kbd.c`

- [ ] Linia **585**: `     // FIXME: Get the event time in the SDL tick time base `
  - **C0220** · [Cod, linia 585](src/core/openbsd/SDL_wscons_kbd.c#L585) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/core/openbsd/SDL_wscons_mouse.c`

- [ ] Linia **68**: `     // FIXME: Get the event time in the SDL tick time base `
  - **C0221** · [Cod, linia 68](src/core/openbsd/SDL_wscons_mouse.c#L68) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/core/windows/SDL_immdevice.c`

- [ ] Linia **128**: `        available and switch automatically. (!!! FIXME...?) */ `
  - **C0224** · [Cod, linia 128](src/core/windows/SDL_immdevice.c#L128) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/dialog/unix/SDL_portaldialog.c`

- [ ] Linia **195**: `             signal_data->callback(signal_data->userdata, result_data, -1); // TODO: Set this to the last selected filter `
  - **C0227** · [Cod, linia 195](src/dialog/unix/SDL_portaldialog.c#L195) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **284**: `         signal_data->callback(signal_data->userdata, path, -1); // TODO: Fetch the index of the filter that was used `
  - **C0228** · [Cod, linia 284](src/dialog/unix/SDL_portaldialog.c#L284) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/dialog/unix/SDL_zenitydialog.c`

- [ ] Linia **50**: `        there aren't others. TODO: find something better. */ `
  - **C0230** · [Cod, linia 50](src/dialog/unix/SDL_zenitydialog.c#L50) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **222**: ` // TODO: Zenity survives termination of the parent `
  - **C0231** · [Cod, linia 222](src/dialog/unix/SDL_zenitydialog.c#L222) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/dialog/windows/SDL_windowsdialog.c`

- [ ] Linia **763**: ` // TODO: The new version of file dialogs `
  - **C0232** · [Cod, linia 763](src/dialog/windows/SDL_windowsdialog.c#L763) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/dynapi/SDL_dynapi.c`

- [ ] Linia **266**: `     char buf[512]; // !!! FIXME: dynamic allocation `
  - **C0233** · [Cod, linia 266](src/dynapi/SDL_dynapi.c#L266) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **399**: `         // !!! FIXME: can maybe handle older versions? `
  - **C0234** · [Cod, linia 399](src/dynapi/SDL_dynapi.c#L399) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/events/SDL_events.c`

- [ ] Linia **1013**: `        FIXME: Does this introduce any other bugs with events at startup? `
  - **C0236** · [Cod, linia 1013](src/events/SDL_events.c#L1013) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/events/SDL_mouse_c.h`

- [ ] Linia **231**: ` // TODO RECONNECT: Set mouse state to "zero" `
  - **C0237** · [Cod, linia 231](src/events/SDL_mouse_c.h#L231) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/events/SDL_mouse.c`

- [ ] Linia **550**: ` /* TODO RECONNECT: Hello from the Wayland video driver! `
  - **C0238** · [Cod, linia 550](src/events/SDL_mouse.c#L550) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/events/SDL_touch.c`

- [ ] Linia **360**: `             // FIXME: maybe we should only restrict to a few SDL_TouchDeviceType `
  - **C0239** · [Cod, linia 360](src/events/SDL_touch.c#L360) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/filesystem/android/SDL_sysfilesystem.c`

- [ ] Linia **58**: `     /* TODO: see https://developer.android.com/reference/android/os/Environment#lfields `
  - **C0240** · [Cod, linia 58](src/filesystem/android/SDL_sysfilesystem.c#L58) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/filesystem/gdk/SDL_sysfilesystem.cpp`

- [ ] Linia **114**: ` // TODO `
  - **C0241** · [Cod, linia 114](src/filesystem/gdk/SDL_sysfilesystem.cpp#L114) · Motiv: SDL_SYS_GetUserFolder returnează SDL_Unsupported() în contextul local; completare de port.

### `src/filesystem/haiku/SDL_sysfilesystem.cc`

- [ ] Linia **128**: `         // TODO: Is Haiku's desktop folder always ~/Desktop/ ? `
  - **C0244** · [Cod, linia 128](src/filesystem/haiku/SDL_sysfilesystem.cc#L128) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/filesystem/n3ds/SDL_sysfilesystem.c`

- [ ] Linia **64**: ` // TODO `
  - **C0245** · [Cod, linia 64](src/filesystem/n3ds/SDL_sysfilesystem.c#L64) · Motiv: SDL_SYS_GetUserFolder returnează SDL_Unsupported() în contextul local; completare de port.

### `src/filesystem/ps2/SDL_sysfilesystem.c`

- [ ] Linia **107**: ` // TODO `
  - **C0246** · [Cod, linia 107](src/filesystem/ps2/SDL_sysfilesystem.c#L107) · Motiv: SDL_SYS_GetUserFolder returnează SDL_Unsupported() în contextul local; completare de port.

### `src/filesystem/psp/SDL_sysfilesystem.c`

- [ ] Linia **76**: ` // TODO `
  - **C0247** · [Cod, linia 76](src/filesystem/psp/SDL_sysfilesystem.c#L76) · Motiv: SDL_SYS_GetUserFolder returnează SDL_Unsupported() în contextul local; completare de port.

### `src/filesystem/riscos/SDL_sysfilesystem.c`

- [ ] Linia **215**: ` // TODO `
  - **C0248** · [Cod, linia 215](src/filesystem/riscos/SDL_sysfilesystem.c#L215) · Motiv: SDL_SYS_GetUserFolder returnează SDL_Unsupported() în contextul local; completare de port.

### `src/filesystem/SDL_filesystem.c`

- [ ] Linia **314**: ``     // !!! FIXME: if we're careful, we can keep a single buffer in `data` that we push and pop paths off the end of as we walk the tree, ``
  - **C0249** · [Cod, linia 314](src/filesystem/SDL_filesystem.c#L314) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **315**: `     // !!! FIXME: and only casefold the new pieces instead of allocating and folding full paths for all of this. `
  - **C0250** · [Cod, linia 315](src/filesystem/SDL_filesystem.c#L315) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/filesystem/vita/SDL_sysfilesystem.c`

- [ ] Linia **78**: ` // TODO `
  - **C0253** · [Cod, linia 78](src/filesystem/vita/SDL_sysfilesystem.c#L78) · Motiv: SDL_SYS_GetUserFolder returnează SDL_Unsupported() în contextul local; completare de port.

### `src/gpu/d3d12/SDL_gpu_d3d12.c`

- [ ] Linia **121**: ` // TODO: do these need to be tuned? `
  - **C0254** · [Cod, linia 121](src/gpu/d3d12/SDL_gpu_d3d12.c#L121) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2473**: `     // FIXME: I think the max can be smaller... `
  - **C0259** · [Cod, linia 2473](src/gpu/d3d12/SDL_gpu_d3d12.c#L2473) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2766**: `     // FIXME: I think the max can be smaller... `
  - **C0261** · [Cod, linia 2766](src/gpu/d3d12/SDL_gpu_d3d12.c#L2766) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **8026**: `         // TODO: compute uniforms `
  - **C0268** · [Cod, linia 8026](src/gpu/d3d12/SDL_gpu_d3d12.c#L8026) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **8112**: `         planeParams.ColorSpace = DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709; // FIXME `
  - **C0269** · [Cod, linia 8112](src/gpu/d3d12/SDL_gpu_d3d12.c#L8112) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/gpu/metal/SDL_gpu_metal.m`

- [ ] Linia **2094**: `     // FIXME: Should this be EXPAND_IF_NEEDED? `
  - **C0277** · [Cod, linia 2094](src/gpu/metal/SDL_gpu_metal.m#L2094) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **3385**: `     // FIXME: Should this use EXPAND_IF_NEEDED? `
  - **C0278** · [Cod, linia 3385](src/gpu/metal/SDL_gpu_metal.m#L3385) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **3519**: `     // FIXME: Should this use EXPAND_IF_NEEDED? `
  - **C0279** · [Cod, linia 3519](src/gpu/metal/SDL_gpu_metal.m#L3519) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/gpu/SDL_gpu.c`

- [ ] Linia **24**: ` // FIXME: This could probably use SDL_ObjectValid `
  - **C0281** · [Cod, linia 24](src/gpu/SDL_gpu.c#L24) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/gpu/vulkan/SDL_gpu_vulkan.c`

- [ ] Linia **6626**: `     // TODO: enable pipeline caching `
  - **C0288** · [Cod, linia 6626](src/gpu/vulkan/SDL_gpu_vulkan.c#L6626) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **10835**: `     // FIXME: Can this just be permanent? `
  - **C0292** · [Cod, linia 10835](src/gpu/vulkan/SDL_gpu_vulkan.c#L10835) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/haptic/android/SDL_syshaptic.c`

- [ ] Linia **296**: `             // !!! TODO: Send a haptic remove event? `
  - **C0302** · [Cod, linia 296](src/haptic/android/SDL_syshaptic.c#L296) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/haptic/darwin/SDL_syshaptic.c`

- [ ] Linia **317**: `             // !!! TODO: Send a haptic remove event? `
  - **C0303** · [Cod, linia 317](src/haptic/darwin/SDL_syshaptic.c#L317) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/haptic/linux/SDL_syshaptic.c`

- [ ] Linia **297**: `     // !!! TODO: Send a haptic add event? `
  - **C0305** · [Cod, linia 297](src/haptic/linux/SDL_syshaptic.c#L297) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **329**: `             // !!! TODO: Send a haptic remove event? `
  - **C0306** · [Cod, linia 329](src/haptic/linux/SDL_syshaptic.c#L329) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/haptic/windows/SDL_windowshaptic.c`

- [ ] Linia **96**: `     // !!! TODO: Send a haptic remove event? `
  - **C0313** · [Cod, linia 96](src/haptic/windows/SDL_windowshaptic.c#L96) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/hidapi/android/hid.cpp`

- [ ] Linia **673**: ` 				return -1; // Read already ongoing, we currently do not serialize, TODO `
  - **C0315** · [Cod, linia 673](src/hidapi/android/hid.cpp#L673) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1144**: ` 	// TODO: Implement `
  - **C0316** · [Cod, linia 1144](src/hidapi/android/hid.cpp#L1144) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1251**: ` // TODO: Implement blocking `
  - **C0317** · [Cod, linia 1251](src/hidapi/android/hid.cpp#L1251) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1258**: ` // TODO: Implement? `
  - **C0318** · [Cod, linia 1258](src/hidapi/android/hid.cpp#L1258) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/hidapi/ios/hid.m`

- [ ] Linia **87**: ` // TODO: create CBUUID's in __attribute__((constructor)) rather than doing [CBUUID UUIDWithString:...] everywhere `
  - **C0321** · [Cod, linia 87](src/hidapi/ios/hid.m#L87) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **438**: ` 				// TODO: we could limit our scan to only peripherals supporting the SteamController service, but `
  - **C0322** · [Cod, linia 438](src/hidapi/ios/hid.m#L438) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/hidapi/libusb/hid.c`

- [ ] Linia **219**: ` /*TODO: Implement this function on hidapi/libusb.. */ `
  - **C0323** · [Cod, linia 219](src/hidapi/libusb/hid.c#L219) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1156**: ` 							/* TODO: have a runtime check for this section. */ `
  - **C0324** · [Cod, linia 1156](src/hidapi/libusb/hid.c#L1156) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/hidapi/mac/hid.c`

- [ ] Linia **978**: ` 	CFRunLoopStop(dev->run_loop); /*TODO: CFRunLoopGetCurrent()*/ `
  - **C0327** · [Cod, linia 978](src/hidapi/mac/hid.c#L978) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/hidapi/src/CMakeLists.txt`

- [ ] Linia **87**: `     # FIXME: https://github.com/libusb/hidapi/issues/492: it is untrivial to set the include path for Framework correctly `
  - **C0328** · [Cod, linia 87](src/hidapi/src/CMakeLists.txt#L87) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/io/generic/SDL_asyncio_generic.c`

- [ ] Linia **49**: `     SDL_Mutex *lock;  // !!! FIXME: we can skip this lock if we have an equivalent of pread/pwrite `
  - **C0331** · [Cod, linia 49](src/io/generic/SDL_asyncio_generic.c#L49) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/io/io_uring/SDL_asyncio_liburing.c`

- [ ] Linia **242**: `             // !!! FIXME: fill in task->error. `
  - **C0333** · [Cod, linia 242](src/io/io_uring/SDL_asyncio_liburing.c#L242) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **313**: `     for (int i = 0; i < num_waiting; i++) {  // !!! FIXME: is there a better way to do this than pushing a zero-timeout request for everything waiting? `
  - **C0334** · [Cod, linia 313](src/io/io_uring/SDL_asyncio_liburing.c#L313) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **357**: `     // !!! FIXME: no idea how large the queue should be. Is 128 overkill or too small? `
  - **C0335** · [Cod, linia 357](src/io/io_uring/SDL_asyncio_liburing.c#L357) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/io/SDL_iostream.c`

- [ ] Linia **171**: `     // FIXME: We may be able to satisfy the seek within buffered data `
  - **C0342** · [Cod, linia 171](src/io/SDL_iostream.c#L171) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/io/windows/SDL_asyncio_windows_ioring.c`

- [ ] Linia **209**: `                 // !!! FIXME: fill in task->error. `
  - **C0345** · [Cod, linia 209](src/io/windows/SDL_asyncio_windows_ioring.c#L209) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **320**: `     // !!! FIXME: no idea how large the queue should be. Is 128 overkill or too small? `
  - **C0346** · [Cod, linia 320](src/io/windows/SDL_asyncio_windows_ioring.c#L320) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/android/SDL_sysjoystick.c`

- [ ] Linia **67**: `  * FIXME: This is only suited for the case where we use a fixed number of buttons determined by ANDROID_MAX_NBUTTONS `
  - **C0351** · [Cod, linia 67](src/joystick/android/SDL_sysjoystick.c#L67) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/emscripten/SDL_sysjoystick_c.h`

- [ ] Linia **46**: `     double axis[64];            // !!! FIXME: don't hardcode 64 on all of these. `
  - **C0353** · [Cod, linia 46](src/joystick/emscripten/SDL_sysjoystick_c.h#L46) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/emscripten/SDL_sysjoystick.c`

- [ ] Linia **98**: `         // TODO: Safari `
  - **C0354** · [Cod, linia 98](src/joystick/emscripten/SDL_sysjoystick.c#L98) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/gdk/SDL_gameinputjoystick.cpp`

- [ ] Linia **983**: `     // FIXME: We can poll this at a much lower rate `
  - **C0355** · [Cod, linia 983](src/joystick/gdk/SDL_gameinputjoystick.cpp#L983) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/hidapi/SDL_hidapi_8bitdo.c`

- [ ] Linia **290**: `     // TODO: If sensor time stamp is sent, these fixed settings from observation can be replaced `
  - **C0356** · [Cod, linia 290](src/joystick/hidapi/SDL_hidapi_8bitdo.c#L290) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/hidapi/SDL_hidapi_gip.c`

- [ ] Linia **1231**: `         /* TODO: Implement Security command property */ `
  - **C0357** · [Cod, linia 1231](src/joystick/hidapi/SDL_hidapi_gip.c#L1231) · Motiv: Comenzi de protocol incomplete; contextul local are handlers neimplementați. Security este nume de comandă, nu dovada unei vulnerabilități.

- [ ] Linia **1312**: `     // TODO `
  - **C0358** · [Cod, linia 1312](src/joystick/hidapi/SDL_hidapi_gip.c#L1312) · Motiv: Comenzi de protocol incomplete; contextul local are handlers neimplementați. Security este nume de comandă, nu dovada unei vulnerabilități.

- [ ] Linia **1701**: `     // TODO `
  - **C0359** · [Cod, linia 1701](src/joystick/hidapi/SDL_hidapi_gip.c#L1701) · Motiv: Comenzi de protocol incomplete; contextul local are handlers neimplementați. Security este nume de comandă, nu dovada unei vulnerabilități.

- [ ] Linia **1736**: `     // TODO `
  - **C0360** · [Cod, linia 1736](src/joystick/hidapi/SDL_hidapi_gip.c#L1736) · Motiv: Comenzi de protocol incomplete; contextul local are handlers neimplementați. Security este nume de comandă, nu dovada unei vulnerabilități.

- [ ] Linia **1969**: `         // TODO `
  - **C0361** · [Cod, linia 1969](src/joystick/hidapi/SDL_hidapi_gip.c#L1969) · Motiv: Comenzi de protocol incomplete; contextul local are handlers neimplementați. Security este nume de comandă, nu dovada unei vulnerabilități.

- [ ] Linia **2413**: `     // TODO `
  - **C0362** · [Cod, linia 2413](src/joystick/hidapi/SDL_hidapi_gip.c#L2413) · Motiv: Comenzi de protocol incomplete; contextul local are handlers neimplementați. Security este nume de comandă, nu dovada unei vulnerabilități.

- [ ] Linia **2424**: `     // TODO `
  - **C0363** · [Cod, linia 2424](src/joystick/hidapi/SDL_hidapi_gip.c#L2424) · Motiv: Comenzi de protocol incomplete; contextul local are handlers neimplementați. Security este nume de comandă, nu dovada unei vulnerabilități.

- [ ] Linia **2435**: `     // TODO `
  - **C0364** · [Cod, linia 2435](src/joystick/hidapi/SDL_hidapi_gip.c#L2435) · Motiv: Comenzi de protocol incomplete; contextul local are handlers neimplementați. Security este nume de comandă, nu dovada unei vulnerabilități.

- [ ] Linia **2446**: `     // TODO `
  - **C0365** · [Cod, linia 2446](src/joystick/hidapi/SDL_hidapi_gip.c#L2446) · Motiv: Comenzi de protocol incomplete; contextul local are handlers neimplementați. Security este nume de comandă, nu dovada unei vulnerabilități.

- [ ] Linia **2590**: `                  * TODO: Is this the correct behavior? `
  - **C0366** · [Cod, linia 2590](src/joystick/hidapi/SDL_hidapi_gip.c#L2590) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/hidapi/SDL_hidapi_ps4.c`

- [ ] Linia **983**: `         // FIXME: Should we send a consistent default effect mask between BT and USB? `
  - **C0368** · [Cod, linia 983](src/joystick/hidapi/SDL_hidapi_ps4.c#L983) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/hidapi/SDL_hidapi_steam_hori.c`

- [ ] Linia **266**: `         // TODO: can we handle the digital trigger mode? The data seems to come through analog regardless of the trigger state `
  - **C0369** · [Cod, linia 266](src/joystick/hidapi/SDL_hidapi_steam_hori.c#L266) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/hidapi/SDL_hidapi_switch2.c`

- [ ] Linia **325**: `     // FIXME: Need to add Bluetooth support `
  - **C0370** · [Cod, linia 325](src/joystick/hidapi/SDL_hidapi_switch2.c#L325) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **608**: `         // FIXME: How many buttons does this have? `
  - **C0371** · [Cod, linia 608](src/joystick/hidapi/SDL_hidapi_switch2.c#L608) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1085**: `                 // FIXME: This shouldn't be necessary, but the rumble thread appears to back up if we don't do this `
  - **C0372** · [Cod, linia 1085](src/joystick/hidapi/SDL_hidapi_switch2.c#L1085) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1144**: `         // FIXME: Need state handling implementation `
  - **C0373** · [Cod, linia 1144](src/joystick/hidapi/SDL_hidapi_switch2.c#L1144) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/hidapi/SDL_hidapi_wii.c`

- [ ] Linia **1446**: `     // FIXME: This should see if the data format is compatible rather than equal `
  - **C0374** · [Cod, linia 1446](src/joystick/hidapi/SDL_hidapi_wii.c#L1446) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/hidapi/SDL_hidapi_zuiki.c`

- [ ] Linia **300**: `         /* todo for switch C key */ `
  - **C0375** · [Cod, linia 300](src/joystick/hidapi/SDL_hidapi_zuiki.c#L300) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/hidapi/steam/controller_structs.h`

- [ ] Linia **312**: ` 	// FIXME figure out a way to grab this stuff over wireless `
  - **C0378** · [Cod, linia 312](src/joystick/hidapi/steam/controller_structs.h#L312) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/linux/SDL_sysjoystick.c`

- [ ] Linia **1391**: `             // TODO: is there any way to detect analog hats in advance via this API? `
  - **C0380** · [Cod, linia 1391](src/joystick/linux/SDL_sysjoystick.c#L1391) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/SDL_gamepad.c`

- [ ] Linia **1191**: `             // FIXME: Should we map this to the left or right side? `
  - **C0382** · [Cod, linia 1191](src/joystick/SDL_gamepad.c#L1191) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1694**: `     // FIXME: We fix these up when loading the mapping, does this ever get hit? `
  - **C0383** · [Cod, linia 1694](src/joystick/SDL_gamepad.c#L1694) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/windows/SDL_windows_gaming_input.c`

- [ ] Linia **745**: `         // FIXME: Can WGI even tell us if trigger rumble is supported? `
  - **C0385** · [Cod, linia 745](src/joystick/windows/SDL_windows_gaming_input.c#L745) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **875**: `             // FIXME: What units are the timestamp we get from GetCurrentReading()? `
  - **C0386** · [Cod, linia 875](src/joystick/windows/SDL_windows_gaming_input.c#L875) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/joystick/windows/SDL_xinputjoystick.c`

- [ ] Linia **398**: `     // FIXME: This does end up making a device ioctl() to query data, we shouldn't do this every update. `
  - **C0387** · [Cod, linia 398](src/joystick/windows/SDL_xinputjoystick.c#L398) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/libm/e_exp.c`

- [ ] Linia **132**: ` 		#else  /* !!! FIXME: check this: "huge * huge" is a compiler warning, maybe they wanted +Inf? */ `
  - **C0388** · [Cod, linia 132](src/libm/e_exp.c#L132) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/locale/unix/SDL_syslocale.c`

- [ ] Linia **67**: `     // !!! FIXME: should we be using setlocale()? Or some D-Bus thing? `
  - **C0389** · [Cod, linia 67](src/locale/unix/SDL_syslocale.c#L67) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/main/gdk/SDL_sysmain_runapp.cpp`

- [ ] Linia **78**: `         // !!! FIXME: This follows the docs exactly, but for some reason still leaks handles on exit? `
  - **C0390** · [Cod, linia 78](src/main/gdk/SDL_sysmain_runapp.cpp#L78) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/power/haiku/SDL_syspower.c`

- [ ] Linia **24**: ` // !!! FIXME: does this thing even work on Haiku? `
  - **C0397** · [Cod, linia 24](src/power/haiku/SDL_syspower.c#L24) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/power/linux/SDL_syspower.c`

- [ ] Linia **150**: `             // !!! FIXME: what exactly _does_ charging/discharging mean? `
  - **C0398** · [Cod, linia 150](src/power/linux/SDL_syspower.c#L150) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **185**: `     // !!! FIXME: calculate (secs). `
  - **C0399** · [Cod, linia 185](src/power/linux/SDL_syspower.c#L185) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/power/macos/SDL_syspower.c`

- [ ] Linia **91**: `             val = -1; // !!! FIXME: calc from timeToFull and capacity? `
  - **C0400** · [Cod, linia 91](src/power/macos/SDL_syspower.c#L91) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/render/direct3d11/SDL_render_d3d11.c`

- [ ] Linia **48**: ` /* !!! FIXME: vertex buffer bandwidth could be lower; only use UV coords when `
  - **C0402** · [Cod, linia 48](src/render/direct3d11/SDL_render_d3d11.c#L48) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **49**: `    !!! FIXME:  textures are needed. */ `
  - **C0403** · [Cod, linia 49](src/render/direct3d11/SDL_render_d3d11.c#L49) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **646**: `         // FIXME: Should we use the default adapter? `
  - **C0404** · [Cod, linia 646](src/render/direct3d11/SDL_render_d3d11.c#L646) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/render/direct3d12/SDL_render_d3d12.c`

- [ ] Linia **50**: ` /* !!! FIXME: vertex buffer bandwidth could be lower; only use UV coords when `
  - **C0406** · [Cod, linia 50](src/render/direct3d12/SDL_render_d3d12.c#L50) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **51**: `    !!! FIXME:  textures are needed. */ `
  - **C0407** · [Cod, linia 51](src/render/direct3d12/SDL_render_d3d12.c#L51) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2900**: `         // FIXME: Xbox doesn't support FUNC_NONE as of the October 2025 GDK, but `
  - **C0410** · [Cod, linia 2900](src/render/direct3d12/SDL_render_d3d12.c#L2900) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/render/gpu/SDL_render_gpu.c`

- [ ] Linia **327**: `         // TODO allocate a persistent transfer buffer `
  - **C0412** · [Cod, linia 327](src/render/gpu/SDL_render_gpu.c#L327) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1159**: ` // *** FIXME *** `
  - **C0414** · [Cod, linia 1159](src/render/gpu/SDL_render_gpu.c#L1159) · Motiv: Contextul local propune reorganizarea uploadurilor pentru a evita ruperea render pass-urilor; optimizare de măsurat.

- [ ] Linia **1626**: `         // FIXME should we return an error if both mailbox and immediate fail? `
  - **C0415** · [Cod, linia 1626](src/render/gpu/SDL_render_gpu.c#L1626) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/render/metal/SDL_render_metal.m`

- [ ] Linia **888**: `     /* TODO: We could have a pool of textures or a MTLHeap we allocate from, `
  - **C0418** · [Cod, linia 888](src/render/metal/SDL_render_metal.m#L888) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **921**: `     /* TODO: This isn't very efficient for the YUV formats, which call `
  - **C0419** · [Cod, linia 921](src/render/metal/SDL_render_metal.m#L921) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1274**: `        angles. Maybe !!! FIXME for later, though. */ `
  - **C0420** · [Cod, linia 1274](src/render/metal/SDL_render_metal.m#L1274) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1731**: `         // !!! FIXME: have a ring of pre-made MTLBuffers we cycle through? How expensive is creation? `
  - **C0421** · [Cod, linia 1731](src/render/metal/SDL_render_metal.m#L1731) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/render/opengl/SDL_render_gl.c`

- [ ] Linia **1356**: `     cache->vertex_array = false;  // !!! FIXME: this resets to false at the end of GL_RunCommandQueue, but we could cache this more aggressively. `
  - **C0429** · [Cod, linia 1356](src/render/opengl/SDL_render_gl.c#L1356) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1357**: `     cache->color_array = false;  // !!! FIXME: this resets to false at the end of GL_RunCommandQueue, but we could cache this more aggressively. `
  - **C0430** · [Cod, linia 1357](src/render/opengl/SDL_render_gl.c#L1357) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1358**: `     cache->texture_array = false;  // !!! FIXME: this resets to false at the end of GL_RunCommandQueue, but we could cache this more aggressively. `
  - **C0431** · [Cod, linia 1358](src/render/opengl/SDL_render_gl.c#L1358) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/render/ps2/SDL_render_ps2.c`

- [ ] Linia **416**: `         // FIXME: What are the settings for this? `
  - **C0433** · [Cod, linia 416](src/render/ps2/SDL_render_ps2.c#L416) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **429**: `         // FIXME: What are the settings for this? `
  - **C0434** · [Cod, linia 429](src/render/ps2/SDL_render_ps2.c#L429) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/render/SDL_render.c`

- [ ] Linia **3136**: `         // FIXME: Are these events guaranteed to be window relative? `
  - **C0438** · [Cod, linia 3136](src/render/SDL_render.c#L3136) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **4269**: `     // We don't intersect the dstrect with the viewport as RenderCopy does because of potential rotation clipping issues... TODO: should we? `
  - **C0439** · [Cod, linia 4269](src/render/SDL_render.c#L4269) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/render/software/SDL_blendfillrect.c`

- [ ] Linia **324**: `     // FIXME: Does this function pointer slow things down significantly? `
  - **C0440** · [Cod, linia 324](src/render/software/SDL_blendfillrect.c#L324) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/render/software/SDL_blendpoint.c`

- [ ] Linia **320**: `     // FIXME: Does this function pointer slow things down significantly? `
  - **C0443** · [Cod, linia 320](src/render/software/SDL_blendpoint.c#L320) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/render/software/SDL_render_sw.c`

- [ ] Linia **677**: `     // !!! FIXME: we can probably avoid some of these calls. `
  - **C0446** · [Cod, linia 677](src/render/software/SDL_render_sw.c#L677) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/render/vitagxm/SDL_render_vita_gxm.c`

- [ ] Linia **1177**: `     // TODO: read from texture rendertarget. `
  - **C0447** · [Cod, linia 1177](src/render/vitagxm/SDL_render_vita_gxm.c#L1177) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/SDL_assert.c`

- [ ] Linia **205**: `             // !!! FIXME: ungrab the input if we're not fullscreen? `
  - **C0448** · [Cod, linia 205](src/SDL_assert.c#L205) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/SDL_hashtable.h`

- [ ] Linia **261**: ``  * !!! FIXME: add note about `threadsafe` here. And update `threadsafety` tags. ``
  - **C0450** · [Cod, linia 261](src/SDL_hashtable.h#L261) · Motiv: Documentarea restricțiilor de relocking și destroy are implicații de utilizare corectă; nu o cursă demonstrată în hashtable.

- [ ] Linia **262**: ``  * !!! FIXME: note that `threadsafe` tables can't be recursively locked, so ``
  - **C0451** · [Cod, linia 262](src/SDL_hashtable.h#L262) · Motiv: Documentarea restricțiilor de relocking și destroy are implicații de utilizare corectă; nu o cursă demonstrată în hashtable.

- [ ] Linia **263**: ``  * !!! FIXME:  you can't use `destroy` callbacks that might end up relocking. ``
  - **C0452** · [Cod, linia 263](src/SDL_hashtable.h#L263) · Motiv: Documentarea restricțiilor de relocking și destroy are implicații de utilizare corectă; nu o cursă demonstrată în hashtable.

### `src/SDL_utils.c`

- [ ] Linia **593**: `                 // FIXME: Need to handle the expand case by reallocating the string `
  - **C0453** · [Cod, linia 593](src/SDL_utils.c#L593) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/sensor/android/SDL_androidsensor.c`

- [ ] Linia **145**: `     // FIXME: Is the sensor list dynamic? `
  - **C0454** · [Cod, linia 145](src/sensor/android/SDL_androidsensor.c#L145) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **223**: `         // FIXME: Maybe add a hint for this? `
  - **C0455** · [Cod, linia 223](src/sensor/android/SDL_androidsensor.c#L223) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/sensor/windows/SDL_windowssensor.c`

- [ ] Linia **202**: `                     // FIXME: Need to know how to interpret the data for this sensor `
  - **C0456** · [Cod, linia 202](src/sensor/windows/SDL_windowssensor.c#L202) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/stdlib/SDL_getenv.c`

- [ ] Linia **280**: `                     // !!! FIXME: InsertIntoHashTable does this lookup too, maybe we should have a means to report that, to avoid duplicate work? `
  - **C0459** · [Cod, linia 280](src/stdlib/SDL_getenv.c#L280) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/stdlib/SDL_string.c`

- [ ] Linia **86**: `     // !!! FIXME: since the hashtable is static, maybe we should binary `
  - **C0460** · [Cod, linia 86](src/stdlib/SDL_string.c#L86) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **87**: `     // !!! FIXME: search it instead of walking the whole bucket. `
  - **C0461** · [Cod, linia 87](src/stdlib/SDL_string.c#L87) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1512**: `             // FIXME: implement more of the format specifiers `
  - **C0462** · [Cod, linia 1512](src/stdlib/SDL_string.c#L1512) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1840**: ` // FIXME: implement more of the format specifiers `
  - **C0463** · [Cod, linia 1840](src/stdlib/SDL_string.c#L1840) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/storage/generic/SDL_genericstorage.c`

- [ ] Linia **129**: `             // FIXME: Should SDL_ReadIO use u64 now...? `
  - **C0464** · [Cod, linia 129](src/storage/generic/SDL_genericstorage.c#L129) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **144**: `     // TODO: Recursively create subdirectories with SDL_CreateDirectory `
  - **C0465** · [Cod, linia 144](src/storage/generic/SDL_genericstorage.c#L144) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **156**: `             // FIXME: Should SDL_WriteIO use u64 now...? `
  - **C0466** · [Cod, linia 156](src/storage/generic/SDL_genericstorage.c#L156) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **171**: `     // TODO: Recursively create subdirectories with SDL_CreateDirectory `
  - **C0467** · [Cod, linia 171](src/storage/generic/SDL_genericstorage.c#L171) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **228**: `     // TODO: There's totally a way to query a folder root's quota... `
  - **C0468** · [Cod, linia 228](src/storage/generic/SDL_genericstorage.c#L228) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/storage/steam/SDL_steamstorage.c`

- [ ] Linia **43**: ` // !!! FIXME: Async API can use SteamRemoteStorage_ReadFileAsync `
  - **C0469** · [Cod, linia 43](src/storage/steam/SDL_steamstorage.c#L43) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **44**: ` // !!! FIXME: Async API can use SteamRemoteStorage_WriteFileAsync `
  - **C0470** · [Cod, linia 44](src/storage/steam/SDL_steamstorage.c#L44) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/test/SDL_test_common.c`

- [ ] Linia **94**: ` /* !!! FIXME: Float32? Sint32? */ `
  - **C0471** · [Cod, linia 94](src/test/SDL_test_common.c#L94) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/thread/generic/SDL_sysrwlock.c`

- [ ] Linia **128**: `             // !!! FIXME: there is a small window where a reader has to lock the mutex, and if we hit that, we will return SDL_RWLOCK_TIMEDOUT even though we could have shared the lock. `
  - **C0474** · [Cod, linia 128](src/thread/generic/SDL_sysrwlock.c#L128) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/thread/ps2/SDL_syssem.c`

- [ ] Linia **46**: `         // TODO: Figure out the limit on the maximum value. `
  - **C0475** · [Cod, linia 46](src/thread/ps2/SDL_syssem.c#L46) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/thread/psp/SDL_syssem.c`

- [ ] Linia **45**: `         // TODO: Figure out the limit on the maximum value. `
  - **C0476** · [Cod, linia 45](src/thread/psp/SDL_syssem.c#L45) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **70**: ` /* TODO: This routine is a bit overloaded. `
  - **C0477** · [Cod, linia 70](src/thread/psp/SDL_syssem.c#L70) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/thread/psp/SDL_systhread.c`

- [ ] Linia **93**: `     // !!! FIXME: is this correct? `
  - **C0478** · [Cod, linia 93](src/thread/psp/SDL_systhread.c#L93) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/thread/pthread/SDL_systhread.c`

- [ ] Linia **191**: `     // FIXME: Setting thread priority does not seem to be supported `
  - **C0479** · [Cod, linia 191](src/thread/pthread/SDL_systhread.c#L191) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/thread/vita/SDL_syssem.c`

- [ ] Linia **46**: `         // TODO: Figure out the limit on the maximum value. `
  - **C0480** · [Cod, linia 46](src/thread/vita/SDL_syssem.c#L46) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **71**: ` /* TODO: This routine is a bit overloaded. `
  - **C0481** · [Cod, linia 71](src/thread/vita/SDL_syssem.c#L71) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/time/ps2/SDL_systime.c`

- [ ] Linia **30**: ` // TODO: Implement this... `
  - **C0482** · [Cod, linia 30](src/time/ps2/SDL_systime.c#L30) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **52**: `     // FIXME: Need implementation `
  - **C0483** · [Cod, linia 52](src/time/ps2/SDL_systime.c#L52) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/android/SDL_androidpen.c`

- [ ] Linia **48**: `         // TODO: Query JNI for pen device info `
  - **C0484** · [Cod, linia 48](src/video/android/SDL_androidpen.c#L48) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **64**: `     // TODO: add more axis `
  - **C0485** · [Cod, linia 64](src/video/android/SDL_androidpen.c#L64) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/cocoa/SDL_cocoaevents.m`

- [ ] Linia **333**: `         SDL_Delay(300); // !!! FIXME: this isn't right. `
  - **C0486** · [Cod, linia 333](src/video/cocoa/SDL_cocoaevents.m#L333) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/cocoa/SDL_cocoaopengl.m`

- [ ] Linia **96**: `         // !!! FIXME: check return values. `
  - **C0494** · [Cod, linia 96](src/video/cocoa/SDL_cocoaopengl.m#L96) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/cocoa/SDL_cocoaopengles.m`

- [ ] Linia **126**: ` // !!! FIXME: commenting out this assertion is (I think) incorrect; figure out why driver_loaded is wrong for ANGLE instead. --ryan. `
  - **C0495** · [Cod, linia 126](src/video/cocoa/SDL_cocoaopengles.m#L126) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/cocoa/SDL_cocoavulkan.m`

- [ ] Linia **222**: `      * TODO: Now that we have SDL_Vulkan_DestroySurface someone with enough `
  - **C0496** · [Cod, linia 222](src/video/cocoa/SDL_cocoavulkan.m#L222) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **300**: `         // TODO: Add CFBridgingRelease(metalview) here perhaps? `
  - **C0497** · [Cod, linia 300](src/video/cocoa/SDL_cocoavulkan.m#L300) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/cocoa/SDL_cocoawindow.m`

- [ ] Linia **549**: ` // !!! FIXME: this should use a hint callback. `
  - **C0499** · [Cod, linia 549](src/video/cocoa/SDL_cocoawindow.m#L549) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1616**: `         // FIXME: Why does the window get hidden? `
  - **C0500** · [Cod, linia 1616](src/video/cocoa/SDL_cocoawindow.m#L1616) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2088**: `         /* TODO: Before implementing direct touch support here, we need to `
  - **C0501** · [Cod, linia 2088](src/video/cocoa/SDL_cocoawindow.m#L2088) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2367**: `             /* FIXME: Should not need to call addChildWindow then orderOut. `
  - **C0502** · [Cod, linia 2367](src/video/cocoa/SDL_cocoawindow.m#L2367) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/emscripten/SDL_emscriptenframebuffer.c`

- [ ] Linia **77**: `         //TODO: this should store a context per canvas `
  - **C0509** · [Cod, linia 77](src/video/emscripten/SDL_emscriptenframebuffer.c#L77) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/emscripten/SDL_emscriptenmouse.c`

- [ ] Linia **179**: `     // TODO: pointer lock isn't actually enabled yet `
  - **C0510** · [Cod, linia 179](src/video/emscripten/SDL_emscriptenmouse.c#L179) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/emscripten/SDL_emscriptenvideo.c`

- [ ] Linia **229**: `         // TODO: Handle parent window when multiple windows can be added in Emscripten builds `
  - **C0511** · [Cod, linia 229](src/video/emscripten/SDL_emscriptenvideo.c#L229) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **574**: `         window->flags &= ~SDL_WINDOW_FILL_DOCUMENT;   // !!! FIXME: should this fail instead? `
  - **C0512** · [Cod, linia 574](src/video/emscripten/SDL_emscriptenvideo.c#L574) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/gdk/SDL_gdktextinput.cpp`

- [ ] Linia **45**: ` // TODO: Have a separate task queue for text input perhaps? `
  - **C0513** · [Cod, linia 45](src/video/gdk/SDL_gdktextinput.cpp#L45) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **282**: `         // FIXME: Password or number scope? `
  - **C0514** · [Cod, linia 282](src/video/gdk/SDL_gdktextinput.cpp#L282) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/haiku/SDL_bmessagebox.cc`

- [ ] Linia **189**: ` 		// TODO: Not Implemented. `
  - **C0515** · [Cod, linia 189](src/video/haiku/SDL_bmessagebox.cc#L189) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/haiku/SDL_bmodes.cc`

- [ ] Linia **213**: `     /* TODO: When Haiku supports multiple display screens, call `
  - **C0518** · [Cod, linia 213](src/video/haiku/SDL_bmodes.cc#L213) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **275**: `     // FIXME: Is the first option always going to be the right one? `
  - **C0520** · [Cod, linia 275](src/video/haiku/SDL_bmodes.cc#L275) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **295**: `     /* FIXME: Is there some way to reboot the OpenGL context?  This doesn't `
  - **C0521** · [Cod, linia 295](src/video/haiku/SDL_bmodes.cc#L295) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/haiku/SDL_bopengl.cc`

- [ ] Linia **51**: ` // FIXME: Is this working correctly? `
  - **C0522** · [Cod, linia 51](src/video/haiku/SDL_bopengl.cc#L51) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **111**: `     /* FIXME: Not sure what flags should be included here; may want to have `
  - **C0523** · [Cod, linia 111](src/video/haiku/SDL_bopengl.cc#L111) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **166**: `     // TODO: Implement this, if necessary? `
  - **C0524** · [Cod, linia 166](src/video/haiku/SDL_bopengl.cc#L166) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **178**: `     // TODO: Implement this, if necessary? `
  - **C0525** · [Cod, linia 178](src/video/haiku/SDL_bopengl.cc#L178) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **182**: ` /* FIXME: This function is meant to clear the OpenGL context when the video `
  - **C0526** · [Cod, linia 182](src/video/haiku/SDL_bopengl.cc#L182) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/haiku/SDL_bopengl.h`

- [ ] Linia **33**: ` extern bool HAIKU_GL_LoadLibrary(SDL_VideoDevice *_this, const char *path);      // FIXME `
  - **C0527** · [Cod, linia 33](src/video/haiku/SDL_bopengl.h#L33) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **34**: ` extern SDL_FunctionPointer HAIKU_GL_GetProcAddress(SDL_VideoDevice *_this, const char *proc); // FIXME `
  - **C0528** · [Cod, linia 34](src/video/haiku/SDL_bopengl.h#L34) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **35**: ` extern void HAIKU_GL_UnloadLibrary(SDL_VideoDevice *_this);                     // TODO `
  - **C0529** · [Cod, linia 35](src/video/haiku/SDL_bopengl.h#L35) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **38**: ` extern bool HAIKU_GL_SetSwapInterval(SDL_VideoDevice *_this, int interval); // TODO `
  - **C0530** · [Cod, linia 38](src/video/haiku/SDL_bopengl.h#L38) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **39**: ` extern bool HAIKU_GL_GetSwapInterval(SDL_VideoDevice *_this, int *interval); // TODO `
  - **C0531** · [Cod, linia 39](src/video/haiku/SDL_bopengl.h#L39) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/haiku/SDL_bvideo.cc`

- [ ] Linia **57**: `     device->internal = NULL; /* FIXME: Is this the cause of some of the `
  - **C0532** · [Cod, linia 57](src/video/haiku/SDL_bvideo.cc#L57) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **60**: ` // TODO: Figure out if any initialization needs to go here `
  - **C0533** · [Cod, linia 60](src/video/haiku/SDL_bvideo.cc#L60) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/haiku/SDL_BWin.h`

- [ ] Linia **530**: `         /* FIXME: Why were these here? `
  - **C0534** · [Cod, linia 530](src/video/haiku/SDL_BWin.h#L530) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/haiku/SDL_bwindow.cc`

- [ ] Linia **57**: `         // TODO: Add support for this flag `
  - **C0536** · [Cod, linia 57](src/video/haiku/SDL_bwindow.cc#L57) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **60**: `         // TODO: Add support for this flag `
  - **C0537** · [Cod, linia 60](src/video/haiku/SDL_bwindow.cc#L60) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **186**: `     // TODO: Implement this! `
  - **C0538** · [Cod, linia 186](src/video/haiku/SDL_bwindow.cc#L186) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/kmsdrm/SDL_kmsdrmmouse.c`

- [ ] Linia **458**: `     // TODO: ? `
  - **C0540** · [Cod, linia 458](src/video/kmsdrm/SDL_kmsdrmmouse.c#L458) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **479**: `             /* !!! FIXME: Some programs expect cursor movement even while they don't do SwapWindow() calls, `
  - **C0541** · [Cod, linia 479](src/video/kmsdrm/SDL_kmsdrmmouse.c#L479) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/kmsdrm/SDL_kmsdrmopengles.c`

- [ ] Linia **202**: `     info.src_w = window->w;  // !!! FIXME: was windata->src_w in the original atomic patch `
  - **C0542** · [Cod, linia 202](src/video/kmsdrm/SDL_kmsdrmopengles.c#L202) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **203**: `     info.src_h = window->h;  // !!! FIXME: was windata->src_h in the original atomic patch `
  - **C0543** · [Cod, linia 203](src/video/kmsdrm/SDL_kmsdrmopengles.c#L203) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **204**: `     info.crtc_w = dispdata->mode.hdisplay;  // !!! FIXME: was windata->output_w in the original atomic patch `
  - **C0544** · [Cod, linia 204](src/video/kmsdrm/SDL_kmsdrmopengles.c#L204) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **205**: `     info.crtc_h = dispdata->mode.vdisplay;  // !!! FIXME: was windata->output_h in the original atomic patch `
  - **C0545** · [Cod, linia 205](src/video/kmsdrm/SDL_kmsdrmopengles.c#L205) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **206**: `     info.crtc_x = 0;  // !!! FIXME: was windata->output_x in the original atomic patch `
  - **C0546** · [Cod, linia 206](src/video/kmsdrm/SDL_kmsdrmopengles.c#L206) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **347**: `     info.src_w = window->w;  // !!! FIXME: was windata->src_w in the original atomic patch `
  - **C0547** · [Cod, linia 347](src/video/kmsdrm/SDL_kmsdrmopengles.c#L347) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **348**: `     info.src_h = window->h;  // !!! FIXME: was windata->src_h in the original atomic patch `
  - **C0548** · [Cod, linia 348](src/video/kmsdrm/SDL_kmsdrmopengles.c#L348) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **349**: `     info.crtc_w = dispdata->mode.hdisplay;  // !!! FIXME: was windata->output_w in the original atomic patch `
  - **C0549** · [Cod, linia 349](src/video/kmsdrm/SDL_kmsdrmopengles.c#L349) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **350**: `     info.crtc_h = dispdata->mode.vdisplay;  // !!! FIXME: was windata->output_h in the original atomic patch `
  - **C0550** · [Cod, linia 350](src/video/kmsdrm/SDL_kmsdrmopengles.c#L350) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **351**: `     info.crtc_x = 0;  // !!! FIXME: was windata->output_x in the original atomic patch `
  - **C0551** · [Cod, linia 351](src/video/kmsdrm/SDL_kmsdrmopengles.c#L351) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/kmsdrm/SDL_kmsdrmvideo.c`

- [ ] Linia **1614**: `     /* TODO : Continue investigating why this doesn't work. We should do this instead `
  - **C0552** · [Cod, linia 1614](src/video/kmsdrm/SDL_kmsdrmvideo.c#L1614) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1618**: ` #if 0  // (note that this code has bitrotted a little, in addition to TODO comment above.) `
  - **C0553** · [Cod, linia 1618](src/video/kmsdrm/SDL_kmsdrmvideo.c#L1618) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1800**: `        FIXME: How do we do that now? Can we get a better idea at the higher level? `
  - **C0554** · [Cod, linia 1800](src/video/kmsdrm/SDL_kmsdrmvideo.c#L1800) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/miniz.h`

- [ ] Linia **213**: `   // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux `
  - **C0555** · [Cod, linia 213](src/video/miniz.h#L213) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/psp/SDL_pspvideo.c`

- [ ] Linia **138**: ` 	// TODO: understand how these work `
  - **C0558** · [Cod, linia 138](src/video/psp/SDL_pspvideo.c#L138) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/qnx/SDL_qnxkeyboard.c`

- [ ] Linia **125**: `     // FIXME: `
  - **C0560** · [Cod, linia 125](src/video/qnx/SDL_qnxkeyboard.c#L125) · Motiv: Continuarea comentariului cere mai multe stări/combinări de taste; input incomplet.

### `src/video/raspberry/SDL_rpimouse.c`

- [ ] Linia **286**: `     /* FIXME: Using UDEV it should be possible to scan all mice `
  - **C0561** · [Cod, linia 286](src/video/raspberry/SDL_rpimouse.c#L286) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/riscos/SDL_riscosvideo.c`

- [ ] Linia **90**: `     // TODO: Support windowed mode `
  - **C0562** · [Cod, linia 90](src/video/riscos/SDL_riscosvideo.c#L90) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/SDL_blit_N.c`

- [ ] Linia **871**: ` // !!!! FIXME: Check for G5 or later, not the cache size! Always prefetch on a G4. `
  - **C0563** · [Cod, linia 871](src/video/SDL_blit_N.c#L871) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/SDL_blit.h`

- [ ] Linia **524**: ` // FIXME: SDL_SIZE_MAX might not be an integer literal `
  - **C0566** · [Cod, linia 524](src/video/SDL_blit.h#L524) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/SDL_egl.c`

- [ ] Linia **1201**: `     /* FIXME: Revisit this check when EGL_EXT_swap_control_tear is published: `
  - **C0568** · [Cod, linia 1201](src/video/SDL_egl.c#L1201) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/SDL_stb.c`

- [ ] Linia **291**: `             /* FIXME: This sucks. It'd be better to allocate the surface first, then `
  - **C0569** · [Cod, linia 291](src/video/SDL_stb.c#L291) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **324**: `             /* FIXME: This sucks. It'd be better to allocate the surface first, then `
  - **C0570** · [Cod, linia 324](src/video/SDL_stb.c#L324) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/SDL_surface.c`

- [ ] Linia **2825**: `         // FIXME: We need code to extract a single macroblock from a YUV surface `
  - **C0571** · [Cod, linia 2825](src/video/SDL_surface.c#L2825) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2902**: `         // FIXME: We need code to extract a single macroblock from a YUV surface `
  - **C0572** · [Cod, linia 2902](src/video/SDL_surface.c#L2902) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/SDL_video.c`

- [ ] Linia **3623**: ` #if defined(SDL_PLATFORM_WIN32) || defined(SDL_PLATFORM_WINGDK) // GDI BitBlt() is way faster than Direct3D dynamic textures right now. (!!! FIXME: is this still true?) `
  - **C0573** · [Cod, linia 3623](src/video/SDL_video.c#L3623) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **4385**: `      * FIXME: Is this fine to just remove this, or should it be preserved just `
  - **C0581** · [Cod, linia 4385](src/video/SDL_video.c#L4385) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **5271**: `         // FIXME: How do we get this information? `
  - **C0582** · [Cod, linia 5271](src/video/SDL_video.c#L5271) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **5640**: ` #if 0 // FIXME `
  - **C0583** · [Cod, linia 5640](src/video/SDL_video.c#L5640) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/stb_image.h`

- [ ] Linia **1440**: `    // @TODO: special case RGB-to-Y (and RGBA-to-YA) for 8-bit-to-16-bit case to keep more precision `
  - **C0587** · [Cod, linia 1440](src/video/stb_image.h#L1440) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **6164**: `    STBI_NOTUSED(tga_x_origin); // @TODO `
  - **C0594** · [Cod, linia 6164](src/video/stb_image.h#L6164) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **6165**: `    STBI_NOTUSED(tga_y_origin); // @TODO `
  - **C0595** · [Cod, linia 6165](src/video/stb_image.h#L6165) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/uikit/SDL_uikitappdelegate.m`

- [ ] Linia **679**: `     // TODO: Handle options `
  - **C0596** · [Cod, linia 679](src/video/uikit/SDL_uikitappdelegate.m#L679) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/uikit/SDL_uikitclipboard.m`

- [ ] Linia **91**: `                                             // TODO: compute mime types `
  - **C0597** · [Cod, linia 91](src/video/uikit/SDL_uikitclipboard.m#L91) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/uikit/SDL_uikitpen.m`

- [ ] Linia **125**: `         const float rotation = rollAngle * radians_to_degrees;  // !!! FIXME: this might need adjustment, I don't have a pencil that supports it. `
  - **C0599** · [Cod, linia 125](src/video/uikit/SDL_uikitpen.m#L125) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **168**: `     // !!! FIXME: no timestamp on these...? `
  - **C0600** · [Cod, linia 168](src/video/uikit/SDL_uikitpen.m#L168) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/uikit/SDL_uikitview.m`

- [ ] Linia **359**: `         // FIXME, need to send: int clicks = (int) touch.tapCount; ? `
  - **C0601** · [Cod, linia 359](src/video/uikit/SDL_uikitview.m#L359) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **395**: `         // FIXME, need to send: int clicks = (int) touch.tapCount; ? `
  - **C0602** · [Cod, linia 395](src/video/uikit/SDL_uikitview.m#L395) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/uikit/SDL_uikitviewcontroller.m`

- [ ] Linia **172**: `     displayLink.preferredFramesPerSecond = 90 / animationInterval;      //TODO: Get frame max frame rate on visionOS `
  - **C0603** · [Cod, linia 172](src/video/uikit/SDL_uikitviewcontroller.m#L172) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/uikit/SDL_uikitvulkan.m`

- [ ] Linia **246**: `      * TODO: Now that we have SDL_Vulkan_DestroySurface someone with enough `
  - **C0604** · [Cod, linia 246](src/video/uikit/SDL_uikitvulkan.m#L246) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **260**: `         // TODO: Add CFBridgingRelease(metalview) here perhaps? `
  - **C0605** · [Cod, linia 260](src/video/uikit/SDL_uikitvulkan.m#L260) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/vivante/SDL_vivantevideo.c`

- [ ] Linia **154**: `     // FIXME: How do we query refresh rate? `
  - **C0606** · [Cod, linia 154](src/video/vivante/SDL_vivantevideo.c#L154) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **324**: `     // FIXME `
  - **C0607** · [Cod, linia 324](src/video/vivante/SDL_vivantevideo.c#L324) · Motiv: Contextul local arată mutare/redimensionare neimplementată; completare de platformă.

- [ ] Linia **330**: `     // FIXME `
  - **C0608** · [Cod, linia 330](src/video/vivante/SDL_vivantevideo.c#L330) · Motiv: Contextul local arată mutare/redimensionare neimplementată; completare de platformă.

### `src/video/wayland/SDL_waylandevents.c`

- [ ] Linia **1725**: `      * TODO: Use a better method of detection? `
  - **C0609** · [Cod, linia 1725](src/video/wayland/SDL_waylandevents.c#L1725) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2163**: `     // TODO: Can this happen? `
  - **C0610** · [Cod, linia 2163](src/video/wayland/SDL_waylandevents.c#L2163) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2766**: `         // TODO: SDL Support more mime types `
  - **C0611** · [Cod, linia 2766](src/video/wayland/SDL_waylandevents.c#L2766) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2897**: `         // TODO: SDL Support more mime types `
  - **C0612** · [Cod, linia 2897](src/video/wayland/SDL_waylandevents.c#L2897) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **3108**: `     // FIXME: Do we care about this event? `
  - **C0613** · [Cod, linia 3108](src/video/wayland/SDL_waylandevents.c#L3108) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **3440**: `     // !!! FIXME: Should hit testing be done if pens generate pointer motion? `
  - **C0614** · [Cod, linia 3440](src/video/wayland/SDL_waylandevents.c#L3440) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **3446**: `             SDL_SendPenTouch(timestamp, instance_id, window, false, true);  // !!! FIXME: how do we know what tip is in use? `
  - **C0615** · [Cod, linia 3446](src/video/wayland/SDL_waylandevents.c#L3446) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **3448**: `             SDL_SendPenTouch(timestamp, instance_id, window, false, false); // !!! FIXME: how do we know what tip is in use? `
  - **C0616** · [Cod, linia 3448](src/video/wayland/SDL_waylandevents.c#L3448) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **3453**: `             SDL_SendPenTouch(timestamp, instance_id, window, false, sdltool->frame.tool_state == WAYLAND_TABLET_TOOL_STATE_DOWN);  // !!! FIXME: how do we know what tip is in use? `
  - **C0617** · [Cod, linia 3453](src/video/wayland/SDL_waylandevents.c#L3453) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/wayland/SDL_waylandmouse.c`

- [ ] Linia **1429**: ` #if 0  // TODO RECONNECT: See waylandvideo.c for more information! `
  - **C0618** · [Cod, linia 1429](src/video/wayland/SDL_waylandmouse.c#L1429) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/wayland/SDL_waylandmouse.h`

- [ ] Linia **37**: ` #if 0  // TODO RECONNECT: See waylandvideo.c for more information! `
  - **C0619** · [Cod, linia 37](src/video/wayland/SDL_waylandmouse.h#L37) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/wayland/SDL_waylandopengles.c`

- [ ] Linia **96**: `     // !!! FIXME: technically, this should be per-context, right? `
  - **C0620** · [Cod, linia 96](src/video/wayland/SDL_waylandopengles.c#L96) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **122**: `      * FIXME: Request EGL_WAYLAND_swap_buffers_with_timeout. `
  - **C0621** · [Cod, linia 122](src/video/wayland/SDL_waylandopengles.c#L122) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/wayland/SDL_waylandsym.h`

- [ ] Linia **95**: ` #if 0 // TODO RECONNECT: See waylandvideo.c for more information! `
  - **C0622** · [Cod, linia 95](src/video/wayland/SDL_waylandsym.h#L95) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/wayland/SDL_waylandvideo.c`

- [ ] Linia **1721**: ` #if 0 // TODO RECONNECT: Uncomment all when https://invent.kde.org/plasma/kwin/-/wikis/Restarting is completed `
  - **C0623** · [Cod, linia 1721](src/video/wayland/SDL_waylandvideo.c#L1721) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/wayland/SDL_waylandwindow.c`

- [ ] Linia **1922**: `      * FIXME: This was originally moved to HideWindow, which _should_ make `
  - **C0624** · [Cod, linia 1922](src/video/wayland/SDL_waylandwindow.c#L1922) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/windows/SDL_windowsevents.c`

- [ ] Linia **379**: `          * FIXME: Update keyboard state `
  - **C0625** · [Cod, linia 379](src/video/windows/SDL_windowsevents.c#L379) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2189**: `                     /* TODO: Can we use GetRawInputDeviceInfo and HID info to `
  - **C0626** · [Cod, linia 2189](src/video/windows/SDL_windowsevents.c#L2189) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2208**: `                     // FIXME: Should we use the input->dwTime field for the tick source of the timestamp? `
  - **C0627** · [Cod, linia 2208](src/video/windows/SDL_windowsevents.c#L2208) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2728**: `     // TODO: can this go before clipcursor? `
  - **C0628** · [Cod, linia 2728](src/video/windows/SDL_windowsevents.c#L2728) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/windows/SDL_windowsgameinput.cpp`

- [ ] Linia **358**: `         // FIXME: We probably need to track key state by keyboardID `
  - **C0629** · [Cod, linia 358](src/video/windows/SDL_windowsgameinput.cpp#L358) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/windows/SDL_windowskeyboard.c`

- [ ] Linia **618**: `     // FIXME: What does this do? `
  - **C0630** · [Cod, linia 618](src/video/windows/SDL_windowskeyboard.c#L618) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/windows/SDL_windowsmodes.c`

- [ ] Linia **91**: `         // FIXME: Can we tell what this will be? `
  - **C0631** · [Cod, linia 91](src/video/windows/SDL_windowsmodes.c#L91) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/windows/SDL_windowsopengl.c`

- [ ] Linia **274**: `    FIXME: Should we weight any particular attribute over any other? `
  - **C0632** · [Cod, linia 274](src/video/windows/SDL_windowsopengl.c#L274) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/windows/SDL_windowsopengles.c`

- [ ] Linia **114**: ` // !!! FIXME: commenting out this assertion is (I think) incorrect; figure out why driver_loaded is wrong for ANGLE instead. --ryan. `
  - **C0633** · [Cod, linia 114](src/video/windows/SDL_windowsopengles.c#L114) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/windows/SDL_windowswindow.c`

- [ ] Linia **749**: `             /* TODO: We have to clear SDL_WINDOW_HIDDEN here to ensure the window flags match the window state. The `
  - **C0634** · [Cod, linia 749](src/video/windows/SDL_windowswindow.c#L749) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/x11/edid-parse.c`

- [ ] Linia **237**: `     /* FIXME: In 1.3 this indicates whether the monitor accepts GTF */ `
  - **C0636** · [Cod, linia 237](src/video/x11/edid-parse.c#L237) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/x11/SDL_x11events.c`

- [ ] Linia **669**: `     // !!! FIXME: we need to regrab this if necessary when the drag is done. `
  - **C0637** · [Cod, linia 669](src/video/x11/SDL_x11events.c#L669) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **704**: `     // !!! FIXME: we need to regrab this if necessary when the drag is done. `
  - **C0638** · [Cod, linia 704](src/video/x11/SDL_x11events.c#L704) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **840**: `         /* !!! FIXME: We were probably storing this on the root window `
  - **C0639** · [Cod, linia 840](src/video/x11/SDL_x11events.c#L840) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **867**: `                     // FIXME: We don't support the X11 INCR protocol for large clipboards. Do we want that? - Yes, yes we do. `
  - **C0640** · [Cod, linia 867](src/video/x11/SDL_x11events.c#L867) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1043**: `     // FIXME: Get the event time in the SDL tick time base `
  - **C0641** · [Cod, linia 1043](src/video/x11/SDL_x11events.c#L1043) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2337**: `     // FIXME: Only need to do this when there are pending focus changes `
  - **C0642** · [Cod, linia 2337](src/video/x11/SDL_x11events.c#L2337) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2340**: `     // FIXME: Only need to do this when there are flashing windows `
  - **C0643** · [Cod, linia 2340](src/video/x11/SDL_x11events.c#L2340) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/x11/SDL_x11keyboard.c`

- [ ] Linia **87**: `         // TODO: Handle groups on the legacy path. `
  - **C0644** · [Cod, linia 87](src/video/x11/SDL_x11keyboard.c#L87) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/x11/SDL_x11modes.c`

- [ ] Linia **1085**: `         /* !!! FIXME: this can get into a problem scenario when a window is `
  - **C0647** · [Cod, linia 1085](src/video/x11/SDL_x11modes.c#L1085) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/x11/SDL_x11mouse.c`

- [ ] Linia **502**: `     // !!! FIXME: should we XSync() here first? `
  - **C0650** · [Cod, linia 502](src/video/x11/SDL_x11mouse.c#L502) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/x11/SDL_x11pen.c`

- [ ] Linia **253**: `             // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now. `
  - **C0653** · [Cod, linia 253](src/video/x11/SDL_x11pen.c#L253) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/x11/SDL_x11toolkit.c`

- [ ] Linia **348**: `             /* TODO: What to do the XFontSet happens to have more than one Thai font? */ `
  - **C0654** · [Cod, linia 348](src/video/x11/SDL_x11toolkit.c#L348) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **366**: `                 /* TODO: Set encoding to none if the font does not actually have any Thai codepoints */ `
  - **C0655** · [Cod, linia 366](src/video/x11/SDL_x11toolkit.c#L366) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/x11/SDL_x11window.c`

- [ ] Linia **366**: `     // FIXME, check the size hints for resizable `
  - **C0657** · [Cod, linia 366](src/video/x11/SDL_x11window.c#L366) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `src/video/x11/SDL_x11xinput2.c`

- [ ] Linia **241**: `      * FIXME:event and err are not needed but if not passed X11_XQueryExtension returns SegmentationFault `
  - **C0658** · [Cod, linia 241](src/video/x11/SDL_x11xinput2.c#L241) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **501**: `     // !!! FIXME: the pen code used to rescan all devices here, but we can do this device-by-device with XI_HierarchyChanged. When do these events fire and why? `
  - **C0659** · [Cod, linia 501](src/video/x11/SDL_x11xinput2.c#L501) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `test/emscripten/driver.py`

- [ ] Linia **86**: `             # FIXME: switch context, verify text of dialog and answer "a" for abort `
  - **C0661** · [Cod, linia 86](test/emscripten/driver.py#L86) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `test/gamepadutils.c`

- [ ] Linia **696**: `         const Sint16 deadzone = 8000; /* !!! FIXME: real deadzone */ `
  - **C0662** · [Cod, linia 696](test/gamepadutils.c#L696) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `test/testaudiohotplug.c`

- [ ] Linia **92**: `                     /* !!! FIXME: this is leaking the stream for now. We'll wire it up to a dictionary or whatever later. */ `
  - **C0664** · [Cod, linia 92](test/testaudiohotplug.c#L92) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **98**: `             /* !!! FIXME: we need to keep track of our streams and destroy them here. */ `
  - **C0665** · [Cod, linia 98](test/testaudiohotplug.c#L98) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `test/testautomation_audio.c`

- [ ] Linia **51**: ` #if 0  /* !!! FIXME: maybe update this? */ `
  - **C0667** · [Cod, linia 51](test/testautomation_audio.c#L51) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **308**: ` #if 0  /* !!! FIXME: maybe update this? */ `
  - **C0668** · [Cod, linia 308](test/testautomation_audio.c#L308) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1520**: ` /* TODO: enable test when SDL_AudioDeviceConnected has been implemented.           */ `
  - **C0669** · [Cod, linia 1520](test/testautomation_audio.c#L1520) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `test/testautomation_intrinsics.c`

- [ ] Linia **15**: ` // FIXME: missing tests for loongarch lsx/lasx `
  - **C0670** · [Cod, linia 15](test/testautomation_intrinsics.c#L15) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **16**: ` // FIXME: missing tests for powerpc altivec `
  - **C0671** · [Cod, linia 16](test/testautomation_intrinsics.c#L16) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `test/testautomation_mouse.c`

- [ ] Linia **492**: `             /* TODO: add tracking of events and check that each call generates a mouse motion event */ `
  - **C0672** · [Cod, linia 492](test/testautomation_mouse.c#L492) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `test/testautomation_platform.c`

- [ ] Linia **177**: `     /* TODO: independently determine and compare values as well */ `
  - **C0673** · [Cod, linia 177](test/testautomation_platform.c#L177) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `test/testevdev.c`

- [ ] Linia **45**: ` /* FIXME: Need CMake tests for this */ `
  - **C0677** · [Cod, linia 45](test/testevdev.c#L45) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **860**: `       /* TODO: The data I have for Steam Deck LCD didn't seem to have `
  - **C0679** · [Cod, linia 860](test/testevdev.c#L860) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1526**: `       /* TODO: Should this be JOYSTICK, or even JOYSTICK|HAS_KEYS? */ `
  - **C0680** · [Cod, linia 1526](test/testevdev.c#L1526) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1591**: `       /* TODO: Should this be JOYSTICK? It has one stick and two buttons */ `
  - **C0681** · [Cod, linia 1591](test/testevdev.c#L1591) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1612**: `       /* TODO: Should this be JOYSTICK, or maybe JOYSTICK|HAS_KEYS? `
  - **C0682** · [Cod, linia 1612](test/testevdev.c#L1612) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1636**: `       /* TODO: Should this be JOYSTICK? */ `
  - **C0683** · [Cod, linia 1636](test/testevdev.c#L1636) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **1997**: `       /* TODO: Ideally we would identify this as a joystick, but there `
  - **C0684** · [Cod, linia 1997](test/testevdev.c#L1997) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2015**: `       /* TODO: Ideally we would identify this as a joystick, but there `
  - **C0686** · [Cod, linia 2015](test/testevdev.c#L2015) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2033**: `       /* TODO: Ideally we would identify this as a joystick by it having `
  - **C0688** · [Cod, linia 2033](test/testevdev.c#L2033) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2053**: `       /* TODO: Ideally we would identify this as a joystick, but there `
  - **C0690** · [Cod, linia 2053](test/testevdev.c#L2053) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **2069**: `       /* TODO: Ideally we would identify this as a joystick, but there `
  - **C0692** · [Cod, linia 2069](test/testevdev.c#L2069) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `test/testfilesystem.c`

- [ ] Linia **173**: `         /* !!! FIXME: put this in a subroutine and make it test more thoroughly (and put it in testautomation). */ `
  - **C0697** · [Cod, linia 173](test/testfilesystem.c#L173) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `test/testprocess.c`

- [ ] Linia **12**: `  * FIXME: Additional tests: `
  - **C0699** · [Cod, linia 12](test/testprocess.c#L12) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

- [ ] Linia **485**: `         /* FIXME: this needs a rate limit */ `
  - **C0700** · [Cod, linia 485](test/testprocess.c#L485) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

### `test/testtray.c`

- [ ] Linia **575**: `     /* TODO: Track memory! */ `
  - **C0702** · [Cod, linia 575](test/testtray.c#L575) · Motiv: Triere funcțională: comportament, compatibilitate sau completare de clarificat; extrasul nu stabilește un impact critic.

## LOW

### `build-scripts/build-web-examples.pl`

- [ ] Linia **398**: `     # !!! FIXME: this needs to generate a preview page for all the categories. `
  - **C0016** · [Cod, linia 398](build-scripts/build-web-examples.pl#L398) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `build-scripts/SDL_migration.cocci`

- [ ] Linia **42**: ` + /* FIXME MIGRATION: maybe move this to a global scope ? */ `
  - **C0018** · [Cod, linia 42](build-scripts/SDL_migration.cocci#L42) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **154**: ` + /* FIXME MIGRATION: check for valid instance */ `
  - **C0019** · [Cod, linia 154](build-scripts/SDL_migration.cocci#L154) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **161**: ` + /* FIXME MIGRATION: check for valid instance */ `
  - **C0020** · [Cod, linia 161](build-scripts/SDL_migration.cocci#L161) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **168**: ` + /* FIXME MIGRATION: check for valid instance */ `
  - **C0021** · [Cod, linia 168](build-scripts/SDL_migration.cocci#L168) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **175**: ` + /* FIXME MIGRATION: check for valid instance */ `
  - **C0022** · [Cod, linia 175](build-scripts/SDL_migration.cocci#L175) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **182**: ` + /* FIXME MIGRATION: check for valid instance */ `
  - **C0023** · [Cod, linia 182](build-scripts/SDL_migration.cocci#L182) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **189**: ` + /* FIXME MIGRATION: check for valid instance */ `
  - **C0024** · [Cod, linia 189](build-scripts/SDL_migration.cocci#L189) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **196**: ` + /* FIXME MIGRATION: check for valid instance */ `
  - **C0025** · [Cod, linia 196](build-scripts/SDL_migration.cocci#L196) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **203**: ` + /* FIXME MIGRATION: check for valid instance */ `
  - **C0026** · [Cod, linia 203](build-scripts/SDL_migration.cocci#L203) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **210**: ` + /* FIXME MIGRATION: SDL_Has3DNow() has been removed; there is no replacement. */ 0 `
  - **C0027** · [Cod, linia 210](build-scripts/SDL_migration.cocci#L210) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **216**: ` + /* FIXME MIGRATION: SDL_HasRDTSC() has been removed; there is no replacement. */ 0 `
  - **C0028** · [Cod, linia 216](build-scripts/SDL_migration.cocci#L216) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **222**: ` + /* FIXME MIGRATION: no longer support by the X11 backend */ NULL `
  - **C0029** · [Cod, linia 222](build-scripts/SDL_migration.cocci#L222) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **228**: ` + /* FIXME MIGRATION: no longer support by the X11 backend */ NULL `
  - **C0030** · [Cod, linia 228](build-scripts/SDL_migration.cocci#L228) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **250**: ` + /* FIXME MIGRATION: SDL_GetRevisionNumber() removed */ 0 `
  - **C0031** · [Cod, linia 250](build-scripts/SDL_migration.cocci#L250) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **268**: ` +  /* FIXME MIGRATION: double-check if you use the returned value of SDL_RWread() */ `
  - **C0032** · [Cod, linia 268](build-scripts/SDL_migration.cocci#L268) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **290**: ` +  /* FIXME MIGRATION: double-check if you use the returned value of SDL_RWwrite() */ `
  - **C0033** · [Cod, linia 290](build-scripts/SDL_migration.cocci#L290) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

- [ ] Linia **2146**: ` + /* FIXME MIGRATION: SDL_WINDOWEVENT_TAKE_FOCUS has been removed; there is no replacement. */ 0 `
  - **C0034** · [Cod, linia 2146](build-scripts/SDL_migration.cocci#L2146) · Motiv: Șablon de avertizare emis la migrarea codului consumatorului, nu dovadă de defect runtime SDL; păstrat pentru trasabilitate.

### `build-scripts/wikiheaders.pl`

- [ ] Linia **249**: `         $retval = "$p\n";  # don't wrap it (!!! FIXME: but maybe parse by lines until we run out of table...) `
  - **C0036** · [Cod, linia 249](build-scripts/wikiheaders.pl#L249) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **759**: `     if (0) {  # !!! FIXME: this lists things that _shouldn't_ be in the headers, like MigrationGuide, etc, but also we don't know if they're functions, macros, etc at this point (can we parse that from the wiki page, though?) `
  - **C0037** · [Cod, linia 759](build-scripts/wikiheaders.pl#L759) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **777**: ` # !!! FIXME: generalize this for other libraries to use. `
  - **C0038** · [Cod, linia 777](build-scripts/wikiheaders.pl#L777) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **893**: `     # !!! FIXME: this gitrev and majorver/etc stuff is copy/pasted a few times now. `
  - **C0039** · [Cod, linia 893](build-scripts/wikiheaders.pl#L893) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **899**: `     # !!! FIXME `
  - **C0040** · [Cod, linia 899](build-scripts/wikiheaders.pl#L899) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **1426**: `             # !!! FIXME: code duplication with typedef processing, below. `
  - **C0041** · [Cod, linia 1426](build-scripts/wikiheaders.pl#L1426) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **1827**: `             die("Unexpected wiki file type. Fixme!"); `
  - **C0042** · [Cod, linia 1827](build-scripts/wikiheaders.pl#L1827) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **1961**: `             # !!! FIXME: lots of code duplication in all of these. `
  - **C0043** · [Cod, linia 1961](build-scripts/wikiheaders.pl#L1961) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **2071**: `             # !!! FIXME: lots of code duplication in all of these. `
  - **C0044** · [Cod, linia 2071](build-scripts/wikiheaders.pl#L2071) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **2086**: `             # !!! FIXME: lots of code duplication in all of these. `
  - **C0045** · [Cod, linia 2086](build-scripts/wikiheaders.pl#L2086) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **2101**: `             # !!! FIXME: lots of code duplication in all of these. `
  - **C0046** · [Cod, linia 2101](build-scripts/wikiheaders.pl#L2101) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **2317**: `                 # !!! FIXME: complain if this isn't a function or macro. `
  - **C0047** · [Cod, linia 2317](build-scripts/wikiheaders.pl#L2317) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **2351**: `                 } elsif (($symtype != 1) && ($symtype != 2) && ($symtype != 5)) {  # !!! FIXME: if 5, make sure it's a function pointer typedef! `
  - **C0048** · [Cod, linia 2351](build-scripts/wikiheaders.pl#L2351) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **2421**: `         # !!! FIXME: uncomment this when we're trying to clean this up in the headers. `
  - **C0049** · [Cod, linia 2421](build-scripts/wikiheaders.pl#L2421) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **2462**: `         if (0) {  # !!! FIXME: this was a useful hack, but this needs to be generalized if we're going to do this always. `
  - **C0050** · [Cod, linia 2462](build-scripts/wikiheaders.pl#L2462) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **2849**: `     # !!! FIXME `
  - **C0051** · [Cod, linia 2849](build-scripts/wikiheaders.pl#L2849) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **2949**: `         $str .= ".\\\"   https://github.com/libsdl-org/SDL/issues/new?title=Misgenerated%20manpage%20for%20$sym\n";  # !!! FIXME: if this becomes a problem for other projects, we'll generalize this. `
  - **C0052** · [Cod, linia 2949](build-scripts/wikiheaders.pl#L2949) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **3104**: `             # !!! FIXME: lots of code duplication in all of these. `
  - **C0053** · [Cod, linia 3104](build-scripts/wikiheaders.pl#L3104) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **3169**: `     # !!! FIXME: code duplication with --copy-to-manpages section. `
  - **C0054** · [Cod, linia 3169](build-scripts/wikiheaders.pl#L3169) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **3186**: `     # !!! FIXME `
  - **C0055** · [Cod, linia 3186](build-scripts/wikiheaders.pl#L3186) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **3250**: `     # !!! FIXME: Maybe put this in the book intro?  print TEXFH $introtxt; `
  - **C0056** · [Cod, linia 3250](build-scripts/wikiheaders.pl#L3250) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **3355**: `             # !!! FIXME: this table parsing has gotten complicated and is pasted three times in this file; move it to a subroutine! `
  - **C0057** · [Cod, linia 3355](build-scripts/wikiheaders.pl#L3355) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **3440**: `             # !!! FIXME: lots of code duplication in all of these. `
  - **C0058** · [Cod, linia 3440](build-scripts/wikiheaders.pl#L3440) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **3463**: `         # !!! FIXME: Maybe put copyright in the book intro? `
  - **C0059** · [Cod, linia 3463](build-scripts/wikiheaders.pl#L3463) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `cmake/CPackProjectConfig.cmake.in`

- [ ] Linia **34**: `     # FIXME: use pre-built/create .DS_Store through AppleScript (CPACK_DMG_DS_STORE/CPACK_DMG_DS_STORE_SETUP_SCRIPT) `
  - **C0060** · [Cod, linia 34](cmake/CPackProjectConfig.cmake.in#L34) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `cmake/macros.cmake`

- [ ] Linia **452**: `     # FIXME: Use $<TARGET_COMPILE_PDB_FILE:${TARGET} once it becomes available (https://gitlab.kitware.com/cmake/cmake/-/issues/25244) `
  - **C0062** · [Cod, linia 452](cmake/macros.cmake#L452) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `cmake/sdlchecks.cmake`

- [ ] Linia **800**: `       # FIXME: Use Find module `
  - **C0065** · [Cod, linia 800](cmake/sdlchecks.cmake#L800) · Motiv: Modernizarea descoperirii dependenței; nu este descris un eșec.

### `cmake/sdlmanpages.cmake`

- [ ] Linia **25**: `   # FIXME: get rid of SYMBOL and let the perl script figure out the dependencies `
  - **C0067** · [Cod, linia 25](cmake/sdlmanpages.cmake#L25) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `CMakeLists.txt`

- [ ] Linia **1366**: `   # !!! FIXME: for later. `
  - **C0073** · [Cod, linia 1366](CMakeLists.txt#L1366) · Motiv: Curățare/modernizare build sau lucru amânat fără impact funcțional demonstrat; continuările pot aparține aceluiași comentariu.

- [ ] Linia **2496**: ``   # !!! FIXME: all the `if(IOS OR TVOS OR VISIONOS)` checks should get merged into one variable, so we're ready for the next platform (or just WatchOS). ``
  - **C0078** · [Cod, linia 2496](CMakeLists.txt#L2496) · Motiv: Curățare/modernizare build sau lucru amânat fără impact funcțional demonstrat; continuările pot aparține aceluiași comentariu.

- [ ] Linia **2499**: `   # !!! FIXME: we need Carbon for some very old API calls in `
  - **C0079** · [Cod, linia 2499](CMakeLists.txt#L2499) · Motiv: Curățare/modernizare build sau lucru amânat fără impact funcțional demonstrat; continuările pot aparține aceluiași comentariu.

- [ ] Linia **2500**: `   # !!! FIXME:  src/video/cocoa/SDL_cocoakeyboard.c, but we should figure out `
  - **C0080** · [Cod, linia 2500](CMakeLists.txt#L2500) · Motiv: Curățare/modernizare build sau lucru amânat fără impact funcțional demonstrat; continuările pot aparține aceluiași comentariu.

- [ ] Linia **2501**: `   # !!! FIXME:  how to dump those. `
  - **C0081** · [Cod, linia 2501](CMakeLists.txt#L2501) · Motiv: Curățare/modernizare build sau lucru amânat fără impact funcțional demonstrat; continuările pot aparține aceluiași comentariu.

- [ ] Linia **2859**: `       # TODO: Use FIND_PACKAGE(OpenGL) instead `
  - **C0083** · [Cod, linia 2859](CMakeLists.txt#L2859) · Motiv: Curățare/modernizare build sau lucru amânat fără impact funcțional demonstrat; continuările pot aparține aceluiași comentariu.

- [ ] Linia **4092**: `   # FIXME: get rid of EXTRA_TEST_LIBS variable `
  - **C0085** · [Cod, linia 4092](CMakeLists.txt#L4092) · Motiv: Curățare/modernizare build sau lucru amânat fără impact funcțional demonstrat; continuările pot aparține aceluiași comentariu.

### `docs/doxyfile`

- [ ] Linia **437**: ` # disable (NO) the todo list. This list is created by putting \todo  `
  - **C0086** · [Cod, linia 437](docs/doxyfile#L437) · Motiv: Potrivire lexicală în text explicativ despre TODO/FIXME; nu constituie în sine o sarcină.

### `docs/README-ios.md`

- [ ] Linia **78**: ` TODO: Add information regarding App Store requirements such as icons, etc. `
  - **C0087** · [Cod, linia 78](docs/README-ios.md#L78) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `docs/README-migration.md`

- [ ] Linia **51**: ` Some macros are renamed and/or removed in SDL3. We have provided a handy Python script [rename_macros.py](https://github.com/libsdl-org/SDL/blob/main/build-scripts/rename_macros.py) to replace these, and also add fixme comments on how to further improve the code: `
  - **C0088** · [Cod, linia 51](docs/README-migration.md#L51) · Motiv: Text explicativ despre avertismentele de migrare; nu o sarcină de implementare.

### `include/build_config/SDL_build_config.h.cmake`

- [ ] Linia **538**: ` /* !!! FIXME: for later cmakedefine SDL_CAMERA_DRIVER_DISK 1 */ `
  - **C0092** · [Cod, linia 538](include/build_config/SDL_build_config.h.cmake#L538) · Motiv: Driver cameră disk marcat pentru mai târziu; extensie opțională.

### `src/atomic/SDL_atomic.c`

- [ ] Linia **28**: ` #ifdef SDL_PLATFORM_MACOS // !!! FIXME: should we favor gcc atomics? `
  - **C0097** · [Cod, linia 28](src/atomic/SDL_atomic.c#L28) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/audio/alsa/SDL_alsa_audio.c`

- [ ] Linia **49**: ` //TODO: cleanup once the code settled down `
  - **C0109** · [Cod, linia 49](src/audio/alsa/SDL_alsa_audio.c#L49) · Motiv: Cleanup, logare sau eliminarea cast-ului const; nu sunt dovezi de scriere invalidă în extras.

- [ ] Linia **363**: `     const int status = ALSA_snd_pcm_recover(pcm, errnum, 0);  // !!! FIXME: third parameter is non-zero to prevent libasound from printing error messages. Should we do that? `
  - **C0111** · [Cod, linia 363](src/audio/alsa/SDL_alsa_audio.c#L363) · Motiv: Cleanup, logare sau eliminarea cast-ului const; nu sunt dovezi de scriere invalidă în extras.

- [ ] Linia **402**: `     Uint8 *sample_buf = (Uint8 *) buffer;  // !!! FIXME: deal with this without casting away constness `
  - **C0112** · [Cod, linia 402](src/audio/alsa/SDL_alsa_audio.c#L402) · Motiv: Cleanup, logare sau eliminarea cast-ului const; nu sunt dovezi de scriere invalidă în extras.

### `src/audio/directsound/SDL_directsound.h`

- [ ] Linia **33**: `     // !!! FIXME: make this a union with capture/playback sections? `
  - **C0114** · [Cod, linia 33](src/audio/directsound/SDL_directsound.h#L33) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/audio/dsp/SDL_dspaudio.c`

- [ ] Linia **23**: ` // !!! FIXME: clean out perror and fprintf calls in here. `
  - **C0115** · [Cod, linia 23](src/audio/dsp/SDL_dspaudio.c#L23) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/audio/jack/SDL_jackaudio.c`

- [ ] Linia **63**: ` // !!! FIXME: this is copy/pasted in several places now `
  - **C0117** · [Cod, linia 63](src/audio/jack/SDL_jackaudio.c#L63) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **271**: ` // !!! FIXME: unify this (PulseAudio has a getAppName, Pipewire has a thing, etc) `
  - **C0118** · [Cod, linia 271](src/audio/jack/SDL_jackaudio.c#L271) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/audio/SDL_audio.c`

- [ ] Linia **403**: ` static void ReleaseAudioDevice(SDL_AudioDevice *device) SDL_NO_THREAD_SAFETY_ANALYSIS  // !!! FIXME: SDL_RELEASE `
  - **C0132** · [Cod, linia 403](src/audio/SDL_audio.c#L403) · Motiv: Adnotări pentru analiza thread safety; nu sunt dovada unei curse.

- [ ] Linia **412**: ` static SDL_LogicalAudioDevice *ObtainLogicalAudioDevice(SDL_AudioDeviceID devid, SDL_AudioDevice **_device) SDL_NO_THREAD_SAFETY_ANALYSIS    // !!! FIXME: SDL_ACQUIRE `
  - **C0133** · [Cod, linia 412](src/audio/SDL_audio.c#L412) · Motiv: Adnotări pentru analiza thread safety; nu sunt dovada unei curse.

- [ ] Linia **466**: ` static SDL_AudioDevice *ObtainPhysicalAudioDevice(SDL_AudioDeviceID devid)  // !!! FIXME: SDL_ACQUIRE `
  - **C0134** · [Cod, linia 466](src/audio/SDL_audio.c#L466) · Motiv: Adnotări pentru analiza thread safety; nu sunt dovada unei curse.

- [ ] Linia **490**: ` static SDL_AudioDevice *ObtainPhysicalAudioDeviceDefaultAllowed(SDL_AudioDeviceID devid)  // !!! FIXME: SDL_ACQUIRE `
  - **C0135** · [Cod, linia 490](src/audio/SDL_audio.c#L490) · Motiv: Adnotări pentru analiza thread safety; nu sunt dovada unei curse.

- [ ] Linia **949**: ` // !!! FIXME: the video subsystem does SDL_VideoInit, not SDL_InitVideo. Make this match. `
  - **C0136** · [Cod, linia 949](src/audio/SDL_audio.c#L949) · Motiv: Convenții de nume/parametri și deduplicare.

- [ ] Linia **1556**: ` // !!! FIXME: SDL convention is for userdata to come first in the callback's params. Fix this at some point. `
  - **C0138** · [Cod, linia 1556](src/audio/SDL_audio.c#L1556) · Motiv: Convenții de nume/parametri și deduplicare.

- [ ] Linia **2405**: `     // !!! FIXME: this duplicates some code we could probably refactor. `
  - **C0141** · [Cod, linia 2405](src/audio/SDL_audio.c#L2405) · Motiv: Convenții de nume/parametri și deduplicare.

- [ ] Linia **2578**: `         // !!! FIXME: this duplicates some code we could probably refactor. `
  - **C0142** · [Cod, linia 2578](src/audio/SDL_audio.c#L2578) · Motiv: Convenții de nume/parametri și deduplicare.

### `src/audio/SDL_audioqueue.c`

- [ ] Linia **51**: `     int chmap_storage[SDL_MAX_CHANNELMAP_CHANNELS];  // !!! FIXME: this needs to grow if SDL ever supports more channels. But if it grows, we should probably be more clever about allocations. `
  - **C0146** · [Cod, linia 51](src/audio/SDL_audioqueue.c#L51) · Motiv: Extensie condiționată de mai multe canale în viitor; nu overflow demonstrat pentru limita actuală.

### `src/audio/SDL_sysaudio.h`

- [ ] Linia **36**: ` // !!! FIXME: These are wordy and unlocalized... `
  - **C0153** · [Cod, linia 36](src/audio/SDL_sysaudio.h#L36) · Motiv: Naming, localizare, simplificare sau extensie condiționată de creșterea limitei canalelor.

- [ ] Linia **49**: ` #define SDL_MAX_CHANNELMAP_CHANNELS 8  // !!! FIXME: if SDL ever supports more channels, clean this out and make those parts dynamic. `
  - **C0154** · [Cod, linia 49](src/audio/SDL_sysaudio.h#L49) · Motiv: Naming, localizare, simplificare sau extensie condiționată de creșterea limitei canalelor.

- [ ] Linia **167**: `     bool ProvidesOwnCallbackThread;  // !!! FIXME: rename this, it's not a callback thread anymore. `
  - **C0155** · [Cod, linia 167](src/audio/SDL_sysaudio.h#L167) · Motiv: Naming, localizare, simplificare sau extensie condiționată de creșterea limitei canalelor.

- [ ] Linia **195**: `     // !!! FIXME: most (all?) of these don't have to be atomic. `
  - **C0157** · [Cod, linia 195](src/audio/SDL_sysaudio.h#L195) · Motiv: Naming, localizare, simplificare sau extensie condiționată de creșterea limitei canalelor.

- [ ] Linia **225**: `     int input_chmap_storage[SDL_MAX_CHANNELMAP_CHANNELS];  // !!! FIXME: this needs to grow if SDL ever supports more channels. But if it grows, we should probably be more clever about allocations. `
  - **C0158** · [Cod, linia 225](src/audio/SDL_sysaudio.h#L225) · Motiv: Naming, localizare, simplificare sau extensie condiționată de creșterea limitei canalelor.

### `src/audio/wasapi/SDL_wasapi.c`

- [ ] Linia **301**: `     ManagementThread = SDL_CreateThreadWithStackSize(ManagementThreadEntry, "SDLWASAPIMgmt", 256 * 1024, &mgmtdata); // !!! FIXME: maybe even smaller stack size? `
  - **C0161** · [Cod, linia 301](src/audio/wasapi/SDL_wasapi.c#L301) · Motiv: Tuning opțional al stackului; nu există măsurătoare care să demonstreze necesitatea.

### `src/camera/android/SDL_camera_android.c`

- [ ] Linia **845**: `     // !!! FIXME: slide this off into a subroutine `
  - **C0167** · [Cod, linia 845](src/camera/android/SDL_camera_android.c#L845) · Motiv: Extragere într-o subrutină, fără impact funcțional descris.

### `src/camera/mediafoundation/SDL_camera_mediafoundation.c`

- [ ] Linia **768**: `     // !!! FIXME: I think it'd be nice to do this without an IMFSourceReader, `
  - **C0177** · [Cod, linia 768](src/camera/mediafoundation/SDL_camera_mediafoundation.c#L768) · Motiv: Alternativă de structurare/refactorizare, fără defect demonstrat.

- [ ] Linia **1077**: `     // !!! FIXME: slide this off into a subroutine `
  - **C0181** · [Cod, linia 1077](src/camera/mediafoundation/SDL_camera_mediafoundation.c#L1077) · Motiv: Alternativă de structurare/refactorizare, fără defect demonstrat.

### `src/camera/SDL_camera.c`

- [ ] Linia **314**: ` static void ObtainPhysicalCameraObj(SDL_Camera *device) SDL_NO_THREAD_SAFETY_ANALYSIS  // !!! FIXME: SDL_ACQUIRE `
  - **C0184** · [Cod, linia 314](src/camera/SDL_camera.c#L314) · Motiv: Adnotări thread safety și convenții de callback.

- [ ] Linia **322**: ` static SDL_Camera *ObtainPhysicalCamera(SDL_CameraID devid)  // !!! FIXME: SDL_ACQUIRE `
  - **C0185** · [Cod, linia 322](src/camera/SDL_camera.c#L322) · Motiv: Adnotări thread safety și convenții de callback.

- [ ] Linia **341**: ` static void ReleaseCamera(SDL_Camera *device) SDL_NO_THREAD_SAFETY_ANALYSIS  // !!! FIXME: SDL_RELEASE `
  - **C0186** · [Cod, linia 341](src/camera/SDL_camera.c#L341) · Motiv: Adnotări thread safety și convenții de callback.

- [ ] Linia **642**: `` // !!! FIXME: this doesn't follow SDL convention of `userdata` being the first param of the callback. ``
  - **C0187** · [Cod, linia 642](src/camera/SDL_camera.c#L642) · Motiv: Adnotări thread safety și convenții de callback.

### `src/camera/SDL_syscamera.h`

- [ ] Linia **202**: ``     SDL_RWLock *device_hash_lock;  // A rwlock that protects `device_hash`   // !!! FIXME: device_hash _also_ has a rwlock, see if we still need this one. ``
  - **C0191** · [Cod, linia 202](src/camera/SDL_syscamera.h#L202) · Motiv: Posibil lock redundant; simplificare doar după demonstrarea contractului de sincronizare.

### `src/core/android/SDL_android.c`

- [ ] Linia **3060**: `     // !!! FIXME: lots of duplication with SDL_GetAndroidExternalStoragePath and SDL_GetAndroidInternalStoragePath; consolidate these functions! `
  - **C0198** · [Cod, linia 3060](src/core/android/SDL_android.c#L3060) · Motiv: Deduplicarea funcțiilor de obținere a căilor.

### `src/core/haiku/SDL_BApp.h`

- [ ] Linia **192**: `     /* FIXME: Bad coding practice, but I can't include SDL_BWin.h here.  Is `
  - **C0203** · [Cod, linia 192](src/core/haiku/SDL_BApp.h#L192) · Motiv: Structurare/include-uri, fără impact funcțional stabilit.

### `src/core/linux/SDL_fcitx.c`

- [ ] Linia **57**: ` // !!! FIXME: should this just be dumped for src/core/unix's SDL_GetAppID()? `
  - **C0216** · [Cod, linia 57](src/core/linux/SDL_fcitx.c#L57) · Motiv: Reutilizarea helperului comun app ID.

### `src/core/windows/SDL_hid.c`

- [ ] Linia **244**: `     // FIXME: Should we log errors? `
  - **C0222** · [Cod, linia 244](src/core/windows/SDL_hid.c#L244) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/core/windows/SDL_immdevice.c`

- [ ] Linia **36**: ` static const ERole SDL_IMMDevice_role = eConsole; // !!! FIXME: should this be eMultimedia? Should be a hint? `
  - **C0223** · [Cod, linia 36](src/core/windows/SDL_immdevice.c#L36) · Motiv: Hint/rol configurabil opțional, fără defect demonstrat.

### `src/core/windows/SDL_windows.h`

- [ ] Linia **134**: ` // !!! FIXME: UTF8ToString() can just be a SDL_strdup() here. `
  - **C0225** · [Cod, linia 134](src/core/windows/SDL_windows.h#L134) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/cpuinfo/SDL_cpuinfo.c`

- [ ] Linia **727**: ` !!! FIXME: Not used at the moment. */ `
  - **C0226** · [Cod, linia 727](src/cpuinfo/SDL_cpuinfo.c#L727) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/events/SDL_events.c`

- [ ] Linia **465**: `     // !!! FIXME: This code is kinda ugly, sorry. `
  - **C0235** · [Cod, linia 465](src/events/SDL_events.c#L465) · Motiv: Comentariu despre lizibilitatea implementării.

### `src/filesystem/haiku/SDL_sysfilesystem.cc`

- [ ] Linia **47**: `     // !!! FIXME: if find_path promises an absolute path, can we dump this and just do SDL_strrchr(name, '/')? `
  - **C0242** · [Cod, linia 47](src/filesystem/haiku/SDL_sysfilesystem.cc#L47) · Motiv: Simplificarea obținerii/procesării căii.

- [ ] Linia **80**: `     // !!! FIXME: is there a better way to do this? `
  - **C0243** · [Cod, linia 80](src/filesystem/haiku/SDL_sysfilesystem.cc#L80) · Motiv: Simplificarea obținerii/procesării căii.

### `src/filesystem/SDL_filesystem.c`

- [ ] Linia **416**: `     // !!! FIXME `
  - **C0251** · [Cod, linia 416](src/filesystem/SDL_filesystem.c#L416) · Motiv: Contextul local este o extensie comentată pentru glob GitIgnore, nu o cale activă demonstrată ca defectă.

### `src/filesystem/unix/SDL_sysfilesystem.c`

- [ ] Linia **200**: `         /* !!! FIXME: after 2.0.6 ships, let's delete this code and just `
  - **C0252** · [Cod, linia 200](src/filesystem/unix/SDL_sysfilesystem.c#L200) · Motiv: Eliminare de cod vechi propusă; verificați compatibilitatea înainte de ștergere.

### `src/gpu/d3d12/SDL_gpu_d3d12.c`

- [ ] Linia **908**: `     // FIXME: these might not be necessary since we're not using custom heaps `
  - **C0255** · [Cod, linia 908](src/gpu/d3d12/SDL_gpu_d3d12.c#L908) · Motiv: Cleanup, limite de diagnostic sau raportare de erori; nu sunt indicate defecte suplimentare de execuție.

- [ ] Linia **1109**: `     // todo cleanup `
  - **C0256** · [Cod, linia 1109](src/gpu/d3d12/SDL_gpu_d3d12.c#L1109) · Motiv: Cleanup, limite de diagnostic sau raportare de erori; nu sunt indicate defecte suplimentare de execuție.

- [ ] Linia **1262**: `     #define MAX_ERROR_LEN 1024 // FIXME: Arbitrary! `
  - **C0258** · [Cod, linia 1262](src/gpu/d3d12/SDL_gpu_d3d12.c#L1262) · Motiv: Cleanup, limite de diagnostic sau raportare de erori; nu sunt indicate defecte suplimentare de execuție.

- [ ] Linia **3886**: `         uavDesc.Buffer.CounterOffsetInBytes = 0; // TODO: support counters? `
  - **C0262** · [Cod, linia 3886](src/gpu/d3d12/SDL_gpu_d3d12.c#L3886) · Motiv: Extensii opționale counters/HDR/SM7/SPIR-V; lipsa suportului nu dovedește un bug în contractul existent.

- [ ] Linia **3893**: `             NULL, // TODO: support counters? `
  - **C0263** · [Cod, linia 3893](src/gpu/d3d12/SDL_gpu_d3d12.c#L3893) · Motiv: Extensii opționale counters/HDR/SM7/SPIR-V; lipsa suportului nu dovedește un bug în contractul existent.

- [ ] Linia **3922**: `     // FIXME: we may not need a CBV since we use root descriptors `
  - **C0264** · [Cod, linia 3922](src/gpu/d3d12/SDL_gpu_d3d12.c#L3922) · Motiv: Cleanup, limite de diagnostic sau raportare de erori; nu sunt indicate defecte suplimentare de execuție.

- [ ] Linia **6656**: `     // FIXME: HDR support would be nice to add, but it seems complicated... `
  - **C0265** · [Cod, linia 6656](src/gpu/d3d12/SDL_gpu_d3d12.c#L6656) · Motiv: Extensii opționale counters/HDR/SM7/SPIR-V; lipsa suportului nu dovedește un bug în contractul existent.

- [ ] Linia **8236**: `                 SET_STRING_ERROR_AND_RETURN("Wait failed", false); // TODO: is there a better way to report this? `
  - **C0270** · [Cod, linia 8236](src/gpu/d3d12/SDL_gpu_d3d12.c#L8236) · Motiv: Cleanup, limite de diagnostic sau raportare de erori; nu sunt indicate defecte suplimentare de execuție.

- [ ] Linia **8292**: `         SET_STRING_ERROR_AND_RETURN("Wait failed", false); // TODO: is there a better way to report this? `
  - **C0271** · [Cod, linia 8292](src/gpu/d3d12/SDL_gpu_d3d12.c#L8292) · Motiv: Cleanup, limite de diagnostic sau raportare de erori; nu sunt indicate defecte suplimentare de execuție.

- [ ] Linia **8578**: `     // TODO SM7: bool has_spirv = SDL_GetBooleanProperty(props, SDL_PROP_GPU_DEVICE_CREATE_SHADERS_SPIRV_BOOLEAN, false); `
  - **C0272** · [Cod, linia 8578](src/gpu/d3d12/SDL_gpu_d3d12.c#L8578) · Motiv: Extensii opționale counters/HDR/SM7/SPIR-V; lipsa suportului nu dovedește un bug în contractul existent.

- [ ] Linia **8579**: `     // TODO SM7: bool supports_spirv = false; `
  - **C0273** · [Cod, linia 8579](src/gpu/d3d12/SDL_gpu_d3d12.c#L8579) · Motiv: Extensii opționale counters/HDR/SM7/SPIR-V; lipsa suportului nu dovedește un bug în contractul existent.

### `src/gpu/metal/SDL_gpu_metal.m`

- [ ] Linia **694**: ` // FIXME: This should be moved into SDL_sysgpu.h `
  - **C0274** · [Cod, linia 694](src/gpu/metal/SDL_gpu_metal.m#L694) · Motiv: Relocare de cod sau posibilă operație redundantă; simplificare condiționată de contract.

- [ ] Linia **1779**: `         // FIXME: Is this necessary? `
  - **C0276** · [Cod, linia 1779](src/gpu/metal/SDL_gpu_metal.m#L1779) · Motiv: Relocare de cod sau posibilă operație redundantă; simplificare condiționată de contract.

### `src/gpu/vulkan/SDL_gpu_vulkan.c`

- [ ] Linia **203**: `         // TODO: use VK_FORMAT_A8_UNORM_KHR from VK_KHR_maintenance5 when available `
  - **C0285** · [Cod, linia 203](src/gpu/vulkan/SDL_gpu_vulkan.c#L203) · Motiv: Extensii de format, configurare opțională, structurare sau diagnostic; fără impact critic stabilit.

- [ ] Linia **214**: `         // TODO: use VK_FORMAT_A4R4G4B4_UNORM_PACK16_EXT from VK_EXT_4444_formats when available `
  - **C0286** · [Cod, linia 214](src/gpu/vulkan/SDL_gpu_vulkan.c#L214) · Motiv: Extensii de format, configurare opțională, structurare sau diagnostic; fără impact critic stabilit.

- [ ] Linia **611**: `     // FIXME: It'd be nice if we didn't have to have this on the texture... `
  - **C0287** · [Cod, linia 611](src/gpu/vulkan/SDL_gpu_vulkan.c#L611) · Motiv: Extensii de format, configurare opțională, structurare sau diagnostic; fără impact critic stabilit.

- [ ] Linia **9984**: `                 NULL, // FIXME: VAllocationCallbacks `
  - **C0290** · [Cod, linia 9984](src/gpu/vulkan/SDL_gpu_vulkan.c#L9984) · Motiv: Extensii de format, configurare opțională, structurare sau diagnostic; fără impact critic stabilit.

- [ ] Linia **10186**: `                 NULL, // FIXME: VAllocationCallbacks `
  - **C0291** · [Cod, linia 10186](src/gpu/vulkan/SDL_gpu_vulkan.c#L10186) · Motiv: Extensii de format, configurare opțională, structurare sau diagnostic; fără impact critic stabilit.

- [ ] Linia **12363**: `     // FIXME: Need better structure for checking vs storing swapchain support details `
  - **C0293** · [Cod, linia 12363](src/gpu/vulkan/SDL_gpu_vulkan.c#L12363) · Motiv: Extensii de format, configurare opțională, structurare sau diagnostic; fără impact critic stabilit.

- [ ] Linia **12881**: `             // FIXME: driverInfo can be a multiline string. `
  - **C0294** · [Cod, linia 12881](src/gpu/vulkan/SDL_gpu_vulkan.c#L12881) · Motiv: Extensii de format, configurare opțională, structurare sau diagnostic; fără impact critic stabilit.

- [ ] Linia **12911**: `     // FIXME: just move this into this function `
  - **C0295** · [Cod, linia 12911](src/gpu/vulkan/SDL_gpu_vulkan.c#L12911) · Motiv: Extensii de format, configurare opțională, structurare sau diagnostic; fără impact critic stabilit.

- [ ] Linia **12990**: `         0,  // !!! FIXME: a real guess here, for a _minimum_ if not a maximum, could be useful. `
  - **C0296** · [Cod, linia 12990](src/gpu/vulkan/SDL_gpu_vulkan.c#L12990) · Motiv: Estimări propuse; comentariul nu demonstrează un rezultat funcțional incorect.

- [ ] Linia **12998**: `         0,  // !!! FIXME: a real guess here, for a _minimum_ if not a maximum, could be useful. `
  - **C0297** · [Cod, linia 12998](src/gpu/vulkan/SDL_gpu_vulkan.c#L12998) · Motiv: Estimări propuse; comentariul nu demonstrează un rezultat funcțional incorect.

- [ ] Linia **13006**: `         0,  // !!! FIXME: a real guess here, for a _minimum_ if not a maximum, could be useful. `
  - **C0298** · [Cod, linia 13006](src/gpu/vulkan/SDL_gpu_vulkan.c#L13006) · Motiv: Estimări propuse; comentariul nu demonstrează un rezultat funcțional incorect.

- [ ] Linia **13014**: `         0,  // !!! FIXME: a real guess here, for a _minimum_ if not a maximum, could be useful. `
  - **C0299** · [Cod, linia 13014](src/gpu/vulkan/SDL_gpu_vulkan.c#L13014) · Motiv: Estimări propuse; comentariul nu demonstrează un rezultat funcțional incorect.

- [ ] Linia **13022**: `         0,  // !!! FIXME: a real guess here, for a _minimum_ if not a maximum, could be useful. `
  - **C0300** · [Cod, linia 13022](src/gpu/vulkan/SDL_gpu_vulkan.c#L13022) · Motiv: Estimări propuse; comentariul nu demonstrează un rezultat funcțional incorect.

- [ ] Linia **13030**: `         0,  // !!! FIXME: a real guess here, for a _minimum_ if not a maximum, could be useful. `
  - **C0301** · [Cod, linia 13030](src/gpu/vulkan/SDL_gpu_vulkan.c#L13030) · Motiv: Estimări propuse; comentariul nu demonstrează un rezultat funcțional incorect.

### `src/haptic/linux/SDL_syshaptic.c`

- [ ] Linia **287**: `     // TODO: should we add instance IDs? `
  - **C0304** · [Cod, linia 287](src/haptic/linux/SDL_syshaptic.c#L287) · Motiv: Extensie a identității dispozitivelor; necesită decizie de API.

### `src/hidapi/doxygen/Doxyfile`

- [ ] Linia **704**: ` # The GENERATE_TODOLIST tag can be used to enable (YES) or disable (NO) the todo `
  - **C0319** · [Cod, linia 704](src/hidapi/doxygen/Doxyfile#L704) · Motiv: Potrivire lexicală în text explicativ despre TODO/FIXME; nu constituie în sine o sarcină.

- [ ] Linia **705**: ` # list. This list is created by putting \todo commands in the documentation. `
  - **C0320** · [Cod, linia 705](src/hidapi/doxygen/Doxyfile#L705) · Motiv: Potrivire lexicală în text explicativ despre TODO/FIXME; nu constituie în sine o sarcină.

### `src/hidapi/libusb/hid.c`

- [ ] Linia **2327**: ` #if 0 /* TODO: Do we need this? */ `
  - **C0325** · [Cod, linia 2327](src/hidapi/libusb/hid.c#L2327) · Motiv: Necesitatea unei porțiuni dezactivate este pusă sub semnul întrebării.

### `src/hidapi/linux/hid.c`

- [ ] Linia **966**: ` 		/* TODO: have a better error reporting via create_device_info_for_device */ `
  - **C0326** · [Cod, linia 966](src/hidapi/linux/hid.c#L966) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/hidapi/windows/hid.c`

- [ ] Linia **1096**: ` 	/* TODO: Merge this with the Linux version. This function is platform-independent. */ `
  - **C0329** · [Cod, linia 1096](src/hidapi/windows/hid.c#L1096) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **1111**: ` 	/* TODO: Merge this functions with the Linux version. This function should be platform independent. */ `
  - **C0330** · [Cod, linia 1111](src/hidapi/windows/hid.c#L1111) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/io/generic/SDL_asyncio_generic.c`

- [ ] Linia **210**: `         max_threadpool_threads = (SDL_GetNumLogicalCPUCores() * 2) + 1;  // !!! FIXME: this should probably have a hint to override. `
  - **C0332** · [Cod, linia 210](src/io/generic/SDL_asyncio_generic.c#L210) · Motiv: Hint opțional pentru dimensionarea threadpool-ului; nu există măsurători.

### `src/joystick/android/SDL_sysjoystick.c`

- [ ] Linia **71**: `     // FIXME: If this function gets too unwieldy in the future, replace with a lookup table `
  - **C0352** · [Cod, linia 71](src/joystick/android/SDL_sysjoystick.c#L71) · Motiv: Refactorizare condiționată de complexitate viitoare.

### `src/joystick/hidapi/SDL_hidapi_lg4ff.c`

- [ ] Linia **450**: `         // TODO do not adjust for MOMO wheels, when support is added `
  - **C0367** · [Cod, linia 450](src/joystick/hidapi/SDL_hidapi_lg4ff.c#L450) · Motiv: Adaptare condiționată de adăugarea suportului MOMO.

### `src/joystick/hidapi/steam/controller_structs.h`

- [ ] Linia **358**: ` 	unsigned char ucGyroDataType; //TODO could maybe find some unused bits in the button field for this info (is only 2bits) `
  - **C0379** · [Cod, linia 358](src/joystick/hidapi/steam/controller_structs.h#L358) · Motiv: Împachetare alternativă a câmpurilor; îmbunătățire opțională.

### `src/joystick/SDL_gamepad.c`

- [ ] Linia **722**: `             // FIXME: Should we have a separate hint for non-HIDAPI JoyCon handling? `
  - **C0381** · [Cod, linia 722](src/joystick/SDL_gamepad.c#L722) · Motiv: Hint separat opțional; necesită justificare de API.

### `src/joystick/SDL_joystick.c`

- [ ] Linia **91**: ` #ifdef SDL_JOYSTICK_USBHID /* !!! FIXME: "USBHID" is a generic name, and doubly-confusing with HIDAPI next to it. This is the *BSD interface, rename this. */ `
  - **C0384** · [Cod, linia 91](src/joystick/SDL_joystick.c#L91) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/main/generic/SDL_sysmain_callbacks.c`

- [ ] Linia **63**: `             // !!! FIXME: this can be made more complicated if we decide to `
  - **C0391** · [Cod, linia 63](src/main/generic/SDL_sysmain_callbacks.c#L63) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **64**: `             // !!! FIXME: optionally hand off callback responsibility to the `
  - **C0392** · [Cod, linia 64](src/main/generic/SDL_sysmain_callbacks.c#L64) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **65**: `             // !!! FIXME: video subsystem (for example, if Wayland has a `
  - **C0393** · [Cod, linia 65](src/main/generic/SDL_sysmain_callbacks.c#L65) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **66**: `             // !!! FIXME: protocol to drive an animation loop, maybe we hand `
  - **C0394** · [Cod, linia 66](src/main/generic/SDL_sysmain_callbacks.c#L66) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **67**: `             // !!! FIXME: off to them here if/when the video subsystem becomes `
  - **C0395** · [Cod, linia 67](src/main/generic/SDL_sysmain_callbacks.c#L67) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

- [ ] Linia **68**: `             // !!! FIXME: initialized). `
  - **C0396** · [Cod, linia 68](src/main/generic/SDL_sysmain_callbacks.c#L68) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/power/windows/SDL_syspower.c`

- [ ] Linia **35**: `         // !!! FIXME: push GetLastError() into SDL_GetError() `
  - **C0401** · [Cod, linia 35](src/power/windows/SDL_syspower.c#L35) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/render/gpu/SDL_pipeline_gpu.c`

- [ ] Linia **145**: `         // !!! FIXME: why don't we have an SDL_alloc_copy function/macro? `
  - **C0411** · [Cod, linia 145](src/render/gpu/SDL_pipeline_gpu.c#L145) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/render/gpu/SDL_render_gpu.c`

- [ ] Linia **1780**: `     // FIXME: What's a good initial size? `
  - **C0416** · [Cod, linia 1780](src/render/gpu/SDL_render_gpu.c#L1780) · Motiv: Tuning al dimensiunii inițiale; fără măsurătoare în inventar.

### `src/render/opengl/SDL_render_gl.c`

- [ ] Linia **973**: ` /* !!! FIXME: all these Queue* calls set up the vertex buffer the way the immediate mode `
  - **C0426** · [Cod, linia 973](src/render/opengl/SDL_render_gl.c#L973) · Motiv: Modernizare opțională vertex buffer/immediate mode; nu este necesară doar pentru eliminarea comentariului.

- [ ] Linia **974**: `    !!! FIXME:  renderer wants it, but this might want to operate differently if we move to `
  - **C0427** · [Cod, linia 974](src/render/opengl/SDL_render_gl.c#L974) · Motiv: Modernizare opțională vertex buffer/immediate mode; nu este necesară doar pentru eliminarea comentariului.

- [ ] Linia **975**: `    !!! FIXME:  VBOs at some point. */ `
  - **C0428** · [Cod, linia 975](src/render/opengl/SDL_render_gl.c#L975) · Motiv: Modernizare opțională vertex buffer/immediate mode; nu este necesară doar pentru eliminarea comentariului.

- [ ] Linia **1365**: `     // !!! FIXME: it'd be nice to use a vertex buffer instead of immediate mode... `
  - **C0432** · [Cod, linia 1365](src/render/opengl/SDL_render_gl.c#L1365) · Motiv: Modernizare opțională vertex buffer/immediate mode; nu este necesară doar pentru eliminarea comentariului.

### `src/SDL_hashtable.c`

- [ ] Linia **25**: `     // TODO: Splitting off values into a separate array might be more cache-friendly `
  - **C0449** · [Cod, linia 25](src/SDL_hashtable.c#L25) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/stdlib/SDL_getenv.c`

- [ ] Linia **61**: `     SDL_Mutex *lock;   // !!! FIXME: reuse SDL_HashTable's lock. `
  - **C0457** · [Cod, linia 61](src/stdlib/SDL_getenv.c#L61) · Motiv: Reutilizare de lock; nu eliminați lock-uri fără demonstrarea echivalenței.

### `src/thread/generic/SDL_sysrwlock.c`

- [ ] Linia **33**: ` // !!! FIXME: this is quite a tapdance with macros and the build system, maybe we can simplify how we do this. --ryan. `
  - **C0472** · [Cod, linia 33](src/thread/generic/SDL_sysrwlock.c#L33) · Motiv: Simplificare build/atomics; păstrați contractul de sincronizare.

- [ ] Linia **99**: `         // !!! FIXME: these don't have to be atomic, we always gate them behind a mutex. `
  - **C0473** · [Cod, linia 99](src/thread/generic/SDL_sysrwlock.c#L99) · Motiv: Simplificare build/atomics; păstrați contractul de sincronizare.

### `src/video/cocoa/SDL_cocoaevents.m`

- [ ] Linia **444**: `     // !!! FIXME: Menu items can't take parameters, just a basic selector, so this should instead call a selector `
  - **C0487** · [Cod, linia 444](src/video/cocoa/SDL_cocoaevents.m#L444) · Motiv: Metadate în panoul About sau mesaj explicativ mai bun.

- [ ] Linia **445**: `     // !!! FIXME: that itself calls -[NSApplication orderFrontStandardAboutPanelWithOptions:optionsDictionary], `
  - **C0488** · [Cod, linia 445](src/video/cocoa/SDL_cocoaevents.m#L445) · Motiv: Metadate în panoul About sau mesaj explicativ mai bun.

- [ ] Linia **446**: `     // !!! FIXME: filling in that NSDictionary with SDL_GetAppMetadataProperty() `
  - **C0489** · [Cod, linia 446](src/video/cocoa/SDL_cocoaevents.m#L446) · Motiv: Metadate în panoul About sau mesaj explicativ mai bun.

- [ ] Linia **668**: `             /* FIXME: this should ideally describe the real reason why the game `
  - **C0490** · [Cod, linia 668](src/video/cocoa/SDL_cocoaevents.m#L668) · Motiv: Metadate în panoul About sau mesaj explicativ mai bun.

### `src/video/cocoa/SDL_cocoamodes.m`

- [ ] Linia **85**: `     // !!! FIXME: maybe track the NSScreen in SDL_DisplayData? `
  - **C0491** · [Cod, linia 85](src/video/cocoa/SDL_cocoamodes.m#L85) · Motiv: Caching/organizare opțională a datelor NSScreen.

### `src/video/cocoa/SDL_cocoamouse.m`

- [ ] Linia **180**: `         case SDL_SYSTEM_CURSOR_WAIT: // !!! FIXME: this is more like WAITARROW `
  - **C0492** · [Cod, linia 180](src/video/cocoa/SDL_cocoamouse.m#L180) · Motiv: Aspect/animație de cursor; impact vizual limitat, nu blocarea inputului.

- [ ] Linia **183**: `         case SDL_SYSTEM_CURSOR_PROGRESS: // !!! FIXME: this is meant to be animated `
  - **C0493** · [Cod, linia 183](src/video/cocoa/SDL_cocoamouse.m#L183) · Motiv: Aspect/animație de cursor; impact vizual limitat, nu blocarea inputului.

### `src/video/cocoa/SDL_cocoawindow.m`

- [ ] Linia **332**: `     // !!! FIXME: is there a better way to do this? `
  - **C0498** · [Cod, linia 332](src/video/cocoa/SDL_cocoawindow.m#L332) · Motiv: Alternativă de implementare nespecificată, fără defect descris.

### `src/video/emscripten/SDL_emscriptenevents.c`

- [ ] Linia **1374**: `     // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do: `
  - **C0503** · [Cod, linia 1374](src/video/emscripten/SDL_emscriptenevents.c#L1374) · Motiv: Înlocuirea integrării existente cu API-uri native când sunt disponibile; dependență externă nevalidată.

- [ ] Linia **1375**: `     // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621 `
  - **C0504** · [Cod, linia 1375](src/video/emscripten/SDL_emscriptenevents.c#L1375) · Motiv: Înlocuirea integrării existente cu API-uri native când sunt disponibile; dependență externă nevalidată.

- [ ] Linia **1378**: `     // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do: `
  - **C0505** · [Cod, linia 1378](src/video/emscripten/SDL_emscriptenevents.c#L1378) · Motiv: Înlocuirea integrării existente cu API-uri native când sunt disponibile; dependență externă nevalidată.

- [ ] Linia **1386**: `     // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do: `
  - **C0506** · [Cod, linia 1386](src/video/emscripten/SDL_emscriptenevents.c#L1386) · Motiv: Înlocuirea integrării existente cu API-uri native când sunt disponibile; dependență externă nevalidată.

- [ ] Linia **1389**: `     // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do: `
  - **C0507** · [Cod, linia 1389](src/video/emscripten/SDL_emscriptenevents.c#L1389) · Motiv: Înlocuirea integrării existente cu API-uri native când sunt disponibile; dependență externă nevalidată.

- [ ] Linia **1390**: `     // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621 `
  - **C0508** · [Cod, linia 1390](src/video/emscripten/SDL_emscriptenevents.c#L1390) · Motiv: Înlocuirea integrării existente cu API-uri native când sunt disponibile; dependență externă nevalidată.

### `src/video/haiku/SDL_bmodes.cc`

- [ ] Linia **41**: ` #define WRAP_BMODE 1 // FIXME: Some debate as to whether this is necessary `
  - **C0516** · [Cod, linia 41](src/video/haiku/SDL_bmodes.cc#L41) · Motiv: Structurare sau helper de debug dezactivat, conform contextului local.

- [ ] Linia **79**: ` /* TODO: `
  - **C0517** · [Cod, linia 79](src/video/haiku/SDL_bmodes.cc#L79) · Motiv: Structurare sau helper de debug dezactivat, conform contextului local.

### `src/video/haiku/SDL_BWin.h`

- [ ] Linia **741**: ` /* FIXME: `
  - **C0535** · [Cod, linia 741](src/video/haiku/SDL_BWin.h#L741) · Motiv: Comentariu explicativ despre flags framebuffer; clarificați scopul editorial înainte de a-l transforma în defect.

### `src/video/miniz.h`

- [ ] Linia **3570**: `   // FIXME: Remove this check? Is it necessary - we already check the filename. `
  - **C0557** · [Cod, linia 3570](src/video/miniz.h#L3570) · Motiv: Posibilă verificare redundantă; nu eliminați defensiva fără teste.

### `src/video/qnx/SDL_qnxgl.c`

- [ ] Linia **230**: `     // !!! FIXME: should we migrate this all over to use SDL_egl.c? `
  - **C0559** · [Cod, linia 230](src/video/qnx/SDL_qnxgl.c#L230) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/video/SDL_bmp.c`

- [ ] Linia **134**: `                 // !!! FIXME: this needsPad calculation can probably be simpler than this. `
  - **C0567** · [Cod, linia 134](src/video/SDL_bmp.c#L134) · Motiv: Simplificarea calculului padding-ului, fără rezultat greșit indicat.

### `src/video/stb_image.h`

- [ ] Linia **1386**: `    // @TODO: move stbi__convert_format to here `
  - **C0584** · [Cod, linia 1386](src/video/stb_image.h#L1386) · Motiv: Relocare de conversii în cod terț; refactorizare fără defect demonstrat.

- [ ] Linia **1412**: `    // @TODO: move stbi__convert_format to here `
  - **C0585** · [Cod, linia 1412](src/video/stb_image.h#L1412) · Motiv: Relocare de conversii în cod terț; refactorizare fără defect demonstrat.

- [ ] Linia **1439**: `    // @TODO: move stbi__convert_format16 to here `
  - **C0586** · [Cod, linia 1439](src/video/stb_image.h#L1439) · Motiv: Relocare de conversii în cod terț; refactorizare fără defect demonstrat.

- [ ] Linia **2158**: `    int restart_interval, todo; `
  - **C0588** · [Cod, linia 2158](src/video/stb_image.h#L2158) · Motiv: Identificatorul todo este variabilă, nu comentariu de lucru; fals pozitiv păstrat, fără fix automat.

- [ ] Linia **3106**: `    j->todo = j->restart_interval ? j->restart_interval : 0x7fffffff; `
  - **C0589** · [Cod, linia 3106](src/video/stb_image.h#L3106) · Motiv: Identificatorul todo este variabilă, nu comentariu de lucru; fals pozitiv păstrat, fără fix automat.

- [ ] Linia **3132**: `                if (--z->todo <= 0) { `
  - **C0590** · [Cod, linia 3132](src/video/stb_image.h#L3132) · Motiv: Identificatorul todo este variabilă, nu comentariu de lucru; fals pozitiv păstrat, fără fix automat.

- [ ] Linia **3164**: `                if (--z->todo <= 0) { `
  - **C0591** · [Cod, linia 3164](src/video/stb_image.h#L3164) · Motiv: Identificatorul todo este variabilă, nu comentariu de lucru; fals pozitiv păstrat, fără fix automat.

- [ ] Linia **3195**: `                if (--z->todo <= 0) { `
  - **C0592** · [Cod, linia 3195](src/video/stb_image.h#L3195) · Motiv: Identificatorul todo este variabilă, nu comentariu de lucru; fals pozitiv păstrat, fără fix automat.

- [ ] Linia **3224**: `                if (--z->todo <= 0) { `
  - **C0593** · [Cod, linia 3224](src/video/stb_image.h#L3224) · Motiv: Identificatorul todo este variabilă, nu comentariu de lucru; fals pozitiv păstrat, fără fix automat.

### `src/video/uikit/SDL_uikitmetalview.m`

- [ ] Linia **102**: `             // TODO: Consider making this configurable or determining it dynamically `
  - **C0598** · [Cod, linia 102](src/video/uikit/SDL_uikitmetalview.m#L102) · Motiv: Configurabilitate/determinare dinamică opțională.

### `src/video/x11/SDL_x11modes.c`

- [ ] Linia **252**: `     // !!! FIXME: a lot of copy/paste from X11_InitModes_XRandR in this function. `
  - **C0645** · [Cod, linia 252](src/video/x11/SDL_x11modes.c#L252) · Motiv: Deduplicare sau eliminare viitoare de workaround; necesită alternativă verificată.

- [ ] Linia **1008**: ` // !!! FIXME: remove this later when we have a better solution. `
  - **C0646** · [Cod, linia 1008](src/video/x11/SDL_x11modes.c#L1008) · Motiv: Deduplicare sau eliminare viitoare de workaround; necesită alternativă verificată.

### `src/video/x11/SDL_x11mouse.c`

- [ ] Linia **38**: ` // FIXME: Find a better place to put this... `
  - **C0648** · [Cod, linia 38](src/video/x11/SDL_x11mouse.c#L38) · Motiv: Relocare/alternativă de implementare, fără defect critic indicat.

- [ ] Linia **358**: `     // FIXME: Is there a better way than this? `
  - **C0649** · [Cod, linia 358](src/video/x11/SDL_x11mouse.c#L358) · Motiv: Relocare/alternativă de implementare, fără defect critic indicat.

- [ ] Linia **509**: `     // !!! FIXME: can we just calculate this from XInput's events? `
  - **C0651** · [Cod, linia 509](src/video/x11/SDL_x11mouse.c#L509) · Motiv: Relocare/alternativă de implementare, fără defect critic indicat.

### `src/video/x11/SDL_x11opengl.c`

- [ ] Linia **447**: `         // !!! FIXME: it would be nice not to make a context here though! `
  - **C0652** · [Cod, linia 447](src/video/x11/SDL_x11opengl.c#L447) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `src/video/x11/SDL_x11window.c`

- [ ] Linia **170**: `     // !!! FIXME: just dereference videodata below instead of copying to locals. `
  - **C0656** · [Cod, linia 170](src/video/x11/SDL_x11window.c#L170) · Motiv: Eliminarea copiilor în variabile locale.

### `test/CMakeLists.txt`

- [ ] Linia **230**: `     # FIXME: only add "${SDL3_BINARY_DIR}/include-config-$<LOWER_CASE:$<CONFIG>>" + include paths of external dependencies `
  - **C0660** · [Cod, linia 230](test/CMakeLists.txt#L230) · Motiv: Restrângerea include paths în build-ul testelor.

### `test/testaudiohotplug.c`

- [ ] Linia **88**: `                     /* !!! FIXME: laziness, this used to loop the audio, but we'll just play it once for now on each connect. */ `
  - **C0663** · [Cod, linia 88](test/testaudiohotplug.c#L88) · Motiv: Comportament opțional al aplicației de test: reluarea audio.

### `test/testaudiorecording.c`

- [ ] Linia **204**: `     SDL_CloseAudioDevice(devid_in);  /* !!! FIXME: use SDL_OpenAudioDeviceStream instead so we can dump this. */ `
  - **C0666** · [Cod, linia 204](test/testaudiorecording.c#L204) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `test/testcamera.c`

- [ ] Linia **255**: `             /* !!! FIXME: only flip if clicked in the area of a "flip" icon. */ `
  - **C0675** · [Cod, linia 255](test/testcamera.c#L255) · Motiv: Polish UI al aplicației de test pentru iconița flip.

- [ ] Linia **376**: `     /* !!! FIXME: Render a "flip" icon if front_camera and back_camera are both != 0. */ `
  - **C0676** · [Cod, linia 376](test/testcamera.c#L376) · Motiv: Polish UI al aplicației de test pentru iconița flip.

### `test/testevdev.c`

- [ ] Linia **92**: `     const char *todo; `
  - **C0678** · [Cod, linia 92](test/testevdev.c#L92) · Motiv: Câmpul todo/utilizarea sa evidențiază probleme cunoscute; nu o sarcină distinctă de comentariile testului.

- [ ] Linia **2001**: `       .todo = "https://github.com/ValveSoftware/Proton/issues/5126", `
  - **C0685** · [Cod, linia 2001](test/testevdev.c#L2001) · Motiv: Câmpul todo/utilizarea sa evidențiază probleme cunoscute; nu o sarcină distinctă de comentariile testului.

- [ ] Linia **2019**: `       .todo = "https://github.com/ValveSoftware/Proton/issues/5126", `
  - **C0687** · [Cod, linia 2019](test/testevdev.c#L2019) · Motiv: Câmpul todo/utilizarea sa evidențiază probleme cunoscute; nu o sarcină distinctă de comentariile testului.

- [ ] Linia **2036**: `       .todo = "https://github.com/ValveSoftware/Proton/issues/5126", `
  - **C0689** · [Cod, linia 2036](test/testevdev.c#L2036) · Motiv: Câmpul todo/utilizarea sa evidențiază probleme cunoscute; nu o sarcină distinctă de comentariile testului.

- [ ] Linia **2057**: `       .todo = "https://github.com/ValveSoftware/Proton/issues/5126", `
  - **C0691** · [Cod, linia 2057](test/testevdev.c#L2057) · Motiv: Câmpul todo/utilizarea sa evidențiază probleme cunoscute; nu o sarcină distinctă de comentariile testului.

- [ ] Linia **2073**: `       .todo = "https://github.com/ValveSoftware/Proton/issues/5126", `
  - **C0693** · [Cod, linia 2073](test/testevdev.c#L2073) · Motiv: Câmpul todo/utilizarea sa evidențiază probleme cunoscute; nu o sarcină distinctă de comentariile testului.

- [ ] Linia **2205**: `             if (t->todo) { `
  - **C0694** · [Cod, linia 2205](test/testevdev.c#L2205) · Motiv: Câmpul todo/utilizarea sa evidențiază probleme cunoscute; nu o sarcină distinctă de comentariile testului.

- [ ] Linia **2206**: `                 printf("\tKnown issue, ignoring: %s\n", t->todo); `
  - **C0695** · [Cod, linia 2206](test/testevdev.c#L2206) · Motiv: Câmpul todo/utilizarea sa evidențiază probleme cunoscute; nu o sarcină distinctă de comentariile testului.

### `test/testffmpeg.c`

- [ ] Linia **1014**: `         /* FIXME: We can actually keep a cache of textures that map to pixel buffers */ `
  - **C0696** · [Cod, linia 1014](test/testffmpeg.c#L1014) · Motiv: Optimizare în aplicația de test; nu performanță măsurată a bibliotecii.

### `test/testmultiaudio.c`

- [ ] Linia **52**: ` #ifdef SDL_PLATFORM_ANDROID  /* !!! FIXME: maybe always create a window, in the SDLTest layer, so these #ifdefs don't have to be here? */ `
  - **C0698** · [Cod, linia 52](test/testmultiaudio.c#L52) · Motiv: Întreținere, diagnostic, refactorizare sau îmbunătățire opțională; nu este indicat un defect critic în extras.

### `test/testprocess.c`

- [ ] Linia **837**: `     /* FIXME: remove child.bat at end of loop and/or create in temporary directory */ `
  - **C0701** · [Cod, linia 837](test/testprocess.c#L837) · Motiv: Igienă pentru fișierul temporar al testului; validați ținta înainte de ștergere.

### `Xcode/XcodeDocSet/Doxyfile`

- [ ] Linia **446**: ` # disable (NO) the todo list. This list is created by putting \todo  `
  - **C0703** · [Cod, linia 446](Xcode/XcodeDocSet/Doxyfile#L446) · Motiv: Potrivire lexicală în text explicativ despre TODO/FIXME; nu constituie în sine o sarcină.
