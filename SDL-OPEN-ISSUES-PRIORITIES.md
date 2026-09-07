# Issue-uri oficiale SDL deschise — priorități

Checklist separat pentru întregul [libsdl-org/SDL](https://github.com/libsdl-org/SDL/issues?q=is%3Aissue%20is%3Aopen): toate platformele, backendurile și versiunile reprezentate în issue-urile deschise. **Pull request-urile și issue-urile închise sunt excluse.** Nu au fost modificate issue-uri pe GitHub.

## Snapshot și acoperire

- Colectare începută: **2026-09-07 17:15:22 UTC**. Revalidarea listei încheiată: **2026-09-07 17:24:11 UTC**.
- **702 issue-uri deschise**, fiecare exact o dată, toate cu `[ ]` nebifat. Numărul a fost confruntat cu totalul GraphQL și cu o enumerare independentă prin GitHub CLI; setul de ID-uri a rămas identic.
- API-ul REST a fost parcurs în 17 pagini de câte cel mult 50 de elemente, eliminând intrările cu `pull_request`. Pentru fiecare issue au fost preluate titlul, descrierea, etichetele, milestone-ul și datele de actualizare.
- Au fost preluate și ultimele maximum două comentarii pentru fiecare issue (1.038 de comentarii în total) și consultate selectiv pentru corectarea trierii. Au fost citite integral descrierile rapoartelor #10857, #16217, #16245 și #15908 și întregul fir de comentarii pentru #10857 și #16217.
- Trierea generală folosește titluri, etichete și extrase din descrieri, nu o investigație completă a fiecărui fir. Nu toate comentariile, logurile, atașamentele, PR-urile sau linkurile externe au fost citite. Titlurile scurte sunt păstrate ca rezumate; titlurile vagi/foarte lungi sunt rezumate editorial și marcate.
- Acesta este un snapshot, nu o listă sincronizată automat. GitHub poate schimba statusurile imediat după captură; colectarea paginată nu este o tranzacție atomică.
- Rapoartele TODO/FIXME locale sunt nemodificate. Nu există o corespondență 1:1 presupusă între comentariile locale și issue-urile upstream.

## Ce înseamnă prioritățile

**Prioritățile sunt evaluarea mea provizorie pentru triere, nu etichete oficiale SDL și nu severități confirmate prin teste locale.** Un issue deschis poate fi o întrebare, o funcționalitate nouă, un defect al aplicației/OS-ului/driverului sau un caz deja remediat care așteaptă retestare.

| Prioritate | Criteriu | Issue-uri |
|---|---|---:|
| URGENT | Semnal de securitate cu exemple/reproducător public indicat: verificarea imediată a expunerii la executare neintenționată. Nu echivalează cu vulnerabilitate/CVE confirmată local. | 2 |
| HIGH | Crash, blocare, acces invalid, pierderea unei funcții principale, rezultate incorecte importante ori degradare severă raportată. Reproduceți prioritar. | 159 |
| MEDIUM | Compatibilitate, funcționalitate incompletă, performanță, teste sau contract neclar; include retestarea fixurilor și urmărirea unor dependențe externe. | 313 |
| LOW | Extensii opționale, redesign, documentație, exemple, cleanup sau urmărire fără lucru SDL restant indicat. | 228 |
| **Total** | **Fără omisiuni sau dublări** | **702** |

Față de inventarul TODO/FIXME, cele două intrări URGENT au rapoarte publice și exemple privind lansarea proceselor, nu doar comentarii de cod. Această prioritate cere validare de securitate imediată; **nu pretinde că release-ul actual a fost testat sau că există două vulnerabilități independente**.

Etichetele `notourbug`, `waiting` și `endoflife` sunt păstrate separat de prioritate. `notourbug` semnalează ownership extern în tracker, nu impact inexistent. `waiting` indică așteptare, nu rezolvare. Milestone-ul este o țintă de organizare upstream, **nu lista versiunilor afectate**.

## Cum se folosește

În fiecare grup, issue-urile sunt ordonate descrescător după număr, nu după severitate internă. Înainte de patch: recitiți firul actual, stabiliți versiunea și contractul, reproduceți, identificați ownership-ul și verificați fixurile deja disponibile. Nu copiați automat patchurile propuse de raportori. Bifați doar după remediere verificată sau închidere explicit justificată. Pentru `notourbug`, acțiunea poate fi retestarea unei dependențe, nu modificarea SDL.

**Verificare efectuată pentru raport:** 702 ID-uri distincte, exact setul issue-urilor OPEN din enumerarea finală, URL-uri oficiale, toate căsuțele nebifate și totaluri reconciliate. Nu s-au rulat compilări, reproduceri sau teste runtime; acest raport nu confirmă defectele și nu e un audit de securitate.

Comandă pentru o enumerare nouă (rezultatul poate diferi de snapshot):

```powershell
gh issue list --repo libsdl-org/SDL --state open --limit 10000 --json number,title,url,state,labels,milestone,updatedAt
```

## URGENT

- [ ] [#16217 — \`SDL\_CreateProcess\` argument escaping on Windows is busted](https://github.com/libsdl-org/SDL/issues/16217)
  - **Motiv:** Raport recent cu exemple de lansare a altui executabil și de executare neintenționată prin argumente batch; triere de securitate imediată, fără reproducere locală.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-09-06 16:32:06 UTC.
  - **Context:** Există un program de test public; un contributor solicită teste/PR. Nu este stabilită o versiune remediată în firul consultat. [Discuție](https://github.com/libsdl-org/SDL/issues/16217#issuecomment-5560599161).

- [ ] [#10857 — Process on Windows is vulnerable to BatBadBut](https://github.com/libsdl-org/SDL/issues/10857)
  - **Motiv:** Raport BatBadBut pentru lansarea explicită de batch/cmd, cu reproducător indicat de contributor; verificarea expunerii și a mitigărilor curente este urgentă.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 19:41:10 UTC.
  - **Context:** Firul este vechi și nu demonstrează singur vulnerabilitatea release-ului actual. Corelați cu #16217; pot fi aspecte ale aceleiași probleme, nu două vulnerabilități independente. [Discuție](https://github.com/libsdl-org/SDL/issues/10857#issuecomment-2352874646).

## HIGH

- [ ] [#16260 — GPU D3D12: \`D3D12\_INTERNAL\_PushUniformData\` dereferences a NULL uniform buffer when the pool cannot supply one](https://github.com/libsdl-org/SDL/issues/16260)
  - **Motiv:** Raport de crash/assert sau acces invalid; verificați reproducerea, versiunea afectată și ownership-ul înainte de fix.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-09-07 05:45:34 UTC.

- [ ] [#16253 — SDL\_SetWindowFullscreen causes system freeze](https://github.com/libsdl-org/SDL/issues/16253)
  - **Motiv:** Este raportată blocarea întregului sistem la fullscreen; prioritate de reproducere, fără a atribui încă defectul SDL sau driverului.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-09-07 16:23:26 UTC.

- [ ] [#16245 — \[X11\] use-after-free in X11\_HandleClipboardEvent when an external owner change races with re-asserting CLIPBOARD ownership (SDL3).](https://github.com/libsdl-org/SDL/issues/16245)
  - **Motiv:** Use-after-free raportat cu reproducător și ASan/Valgrind; investigație prioritară de lifetime. Nu este demonstrată executarea de cod.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.4.18` · Actualizat: 2026-09-04 18:47:43 UTC.
  - **Context:** Un contributor poate încă produce crash cu fixul propus și indică o altă direcție de reparare. [Discuție](https://github.com/libsdl-org/SDL/issues/16245#issuecomment-5545057732).

- [ ] [#16242 — x11: slave pointer button events dropped when window lacks keyboard focus (breaks remote-control tools)](https://github.com/libsdl-org/SDL/issues/16242)
  - **Motiv:** Este raportată pierderea unei funcții principale (input/audio/afișare) în scenariul afectat, nu doar o extensie lipsă.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-09-04 05:03:15 UTC.

- [ ] [#16241 — cocoa: synthetic mouse clicks (remote control/accessibility) are dropped while a GCMouse device is connected](https://github.com/libsdl-org/SDL/issues/16241)
  - **Motiv:** Este raportată pierderea unei funcții principale (input/audio/afișare) în scenariul afectat, nu doar o extensie lipsă.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-09-04 05:03:02 UTC.

- [ ] [#16240 — Closing a fullscreen window sometimes results in X11 error](https://github.com/libsdl-org/SDL/issues/16240)
  - **Motiv:** Eroare de backend sau rezultate de randare neconforme raportate; reproducere și verificare vizuală necesare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.4.18` · Actualizat: 2026-09-04 22:29:06 UTC.

- [ ] [#16236 — when  microphone access is denied, the device maybe can't enumerate by SDL\_GetAudioRecordingDevices() on operating window](https://github.com/libsdl-org/SDL/issues/16236)
  - **Motiv:** Este raportată pierderea unei funcții principale (input/audio/afișare) în scenariul afectat, nu doar o extensie lipsă.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-09-04 07:18:26 UTC.

- [ ] [#16212 — Gravis Xterminator Force causes crashes](https://github.com/libsdl-org/SDL/issues/16212)
  - **Motiv:** Raport de crash/assert sau acces invalid; verificați reproducerea, versiunea afectată și ownership-ul înainte de fix.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-08-29 04:33:11 UTC.

- [ ] [#16201 — Windows IME: candidate list reports an absolute selection index against a page-local array](https://github.com/libsdl-org/SDL/issues/16201)
  - **Motiv:** Indexul candidatului IME raportat poate depăși array-ul livrat aplicației; verificați contractul și siguranța consumatorilor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-26 14:49:42 UTC.

- [ ] [#16174 — KMSDRM: no fallback when an async pageflip is rejected, so every frame fails on drivers that advertise DRM\_CAP\_ASYNC\_PAGE\_FLIP without supporting it](https://github.com/libsdl-org/SDL/issues/16174)
  - **Motiv:** Este raportată pierderea unei funcții principale (input/audio/afișare) în scenariul afectat, nu doar o extensie lipsă.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-20 14:51:37 UTC.

- [ ] [#16163 — X11/XWayland: cached master-device valuator mode corrupts relative mouse motion after source transition](https://github.com/libsdl-org/SDL/issues/16163)
  - **Motiv:** Este raportată pierderea unei funcții principale (input/audio/afișare) în scenariul afectat, nu doar o extensie lipsă.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-08-31 16:05:47 UTC.

- [ ] [#16161 — iOS: Screen Mirroring / AirPlay broken since UIScene support in 3.4](https://github.com/libsdl-org/SDL/issues/16161)
  - **Motiv:** Este raportată pierderea unei funcții principale (input/audio/afișare) în scenariul afectat, nu doar o extensie lipsă.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.4.18` · Actualizat: 2026-09-01 22:05:53 UTC.

- [ ] [#16136 — kmsdrm: SDL3 doesn't work on imx6 with drmkms](https://github.com/libsdl-org/SDL/issues/16136)
  - **Motiv:** Este raportată pierderea unei funcții principale (input/audio/afișare) în scenariul afectat, nu doar o extensie lipsă.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.4.18` · Actualizat: 2026-09-02 15:59:14 UTC.

- [ ] [#16133 — SDL\_audio.c assert in SDL\_AddAudioDevice when PC returns from sleep](https://github.com/libsdl-org/SDL/issues/16133)
  - **Motiv:** Raport de crash/assert sau acces invalid; verificați reproducerea, versiunea afectată și ownership-ul înainte de fix.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.4.18` · Actualizat: 2026-09-02 14:46:01 UTC.

- [ ] [#16114 — D3D12/GDK: crash in ID3D12GraphicsCommandList::Reset (from CleanCommandBuffer) on Xbox at startup](https://github.com/libsdl-org/SDL/issues/16114)
  - **Motiv:** Raport de crash/assert sau acces invalid; verificați reproducerea, versiunea afectată și ownership-ul înainte de fix.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.4.18` · Actualizat: 2026-09-01 22:38:42 UTC.

- [ ] [#16105 — \[macOS\] Segmentation fault in Cocoa\_HandleMouseEvent during SDL\_SetWindowSize (via sdl2-compat)](https://github.com/libsdl-org/SDL/issues/16105)
  - **Motiv:** Raport de crash/assert sau acces invalid; verificați reproducerea, versiunea afectată și ownership-ul înainte de fix.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-09-02 15:14:34 UTC.

- [ ] [#16087 — testyuv --all fails OpenGL UYVY tests on macOS](https://github.com/libsdl-org/SDL/issues/16087)
  - **Motiv:** Eroare de backend sau rezultate de randare neconforme raportate; reproducere și verificare vizuală necesare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-30 23:47:26 UTC.

- [ ] [#16085 — D3D12: crearea pipeline-ului grafic eșuează pentru un triunghi fullscreen minimal](https://github.com/libsdl-org/SDL/issues/16085)
  - Rezumat editorial; titlul integral este disponibil în issue.
  - **Motiv:** Este raportată pierderea unei funcții principale (input/audio/afișare) în scenariul afectat, nu doar o extensie lipsă.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-08-01 14:05:10 UTC.

- [ ] [#16078 — Android: SDL\_ShowSimpleMessageBox causes fatal exception if used in SDL\_AppQuit](https://github.com/libsdl-org/SDL/issues/16078)
  - **Motiv:** Raport de crash/assert sau acces invalid; verificați reproducerea, versiunea afectată și ownership-ul înainte de fix.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-10 02:14:14 UTC.

- [ ] [#16038 — SDL\_Renderer D3D12 is not paired with other renderers](https://github.com/libsdl-org/SDL/issues/16038)
  - **Motiv:** Randare/clipping/blending incorect raportat pe funcționalitate existentă; necesită teste de conformance.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-08-03 15:10:41 UTC.

- [ ] [#16029 — PSP: SDL\_RenderClear does not clear entire target texture](https://github.com/libsdl-org/SDL/issues/16029)
  - **Motiv:** Randare/clipping/blending incorect raportat pe funcționalitate existentă; necesită teste de conformance.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-02 15:34:03 UTC.

- [ ] [#15999 — Failing activity recreation when SDL\_ANDROID\_ALLOW\_RECREATE\_ACTIVITY is 1](https://github.com/libsdl-org/SDL/issues/15999)
  - **Motiv:** Crash/assert sau lifecycle invalid raportat; reproducere și verificarea condițiilor de activare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-20 13:20:34 UTC.

- [ ] [#15964 — Drawing with srgb\_linear gpu renderer has incorrect colors.](https://github.com/libsdl-org/SDL/issues/15964)
  - **Motiv:** Randare/clipping/blending incorect raportat pe funcționalitate existentă; necesită teste de conformance.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-07-09 23:46:17 UTC.

- [ ] [#15947 — GPU/Metal: fence busyloop — please backport 514b26e4c to release-3.4.x; wait-any path still spins on main](https://github.com/libsdl-org/SDL/issues/15947)
  - **Motiv:** Degradare severă de CPU/audio raportată pe calea uzuală; verificați măsurătorile și versiunea/backportul.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-26 20:12:53 UTC.

- [ ] [#15908 — SDL\_ShowSaveFileDialog should expose extra settings](https://github.com/libsdl-org/SDL/issues/15908)
  - **Motiv:** Dialogul verifică numele introdus, iar aplicația poate salva cu o extensie adăugată ulterior; verificați riscul de overwrite neintenționat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-16 23:18:00 UTC.
  - **Context:** Maintainerul discută o extensie cross-platform a dialogurilor. Nu este dovada că SDL scrie sau suprascrie singur fișierul. [Discuție](https://github.com/libsdl-org/SDL/issues/15908#issuecomment-4997418444).

- [ ] [#15899 — Fix for macOS embedding origin/bounds mismatch when using SDL\_WINDOW\_EXTERNAL with Metal (#12141)](https://github.com/libsdl-org/SDL/issues/15899)
  - **Motiv:** Randare/clipping/blending incorect raportat pe funcționalitate existentă; necesită teste de conformance.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-29 16:36:19 UTC.

- [ ] [#15882 — Software alpha blending issue (SDL2)](https://github.com/libsdl-org/SDL/issues/15882)
  - **Motiv:** Randare/clipping/blending incorect raportat pe funcționalitate existentă; necesită teste de conformance.
  - **GitHub:** OPEN · Etichete: — · Milestone: `2.x` · Actualizat: 2026-07-04 00:15:23 UTC.

- [ ] [#15866 — \[SDL\_Render D3D11\] Crash on window maximize via D3D11\_CreateWindowSizeDependentResources → ResizeBuffers on NVIDIA Optimus laptop (driver bug; seeking workaround)](https://github.com/libsdl-org/SDL/issues/15866)
  - **Motiv:** Crash de prezentare pe o configurație Optimus; sever pentru utilizator, dar ownership-ul este probabil la driver.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-07-26 20:28:00 UTC.
  - **Context:** Maintainerul consideră un workaround prin recrearea swapchain-ului costisitor și nu justifică aplicarea lui globală. [Discuție](https://github.com/libsdl-org/SDL/issues/15866#issuecomment-4762767907).

- [ ] [#15843 — Inconsistent handling of NULL with SDL\_SetClipboardData & SDL\_GetClipboardData](https://github.com/libsdl-org/SDL/issues/15843)
  - **Motiv:** Contractul NULL/lungime pentru clipboard este inconsistent conform raportului; verificați validitatea memoriei și interoperabilitatea.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-06-17 09:12:35 UTC.

- [ ] [#15799 — Potential memory leak with SDL3 GPU Renderer and SDL\_RenderTexture](https://github.com/libsdl-org/SDL/issues/15799)
  - **Motiv:** Acumulare de memorie disproporționată la randarea atlasurilor; verificați batching/flush versus leak.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-07-26 20:35:30 UTC.
  - **Context:** Discuția distinge coada de comenzi de memoria persistentă după exit; cea din urmă nu mai este reprodusă constant după update de sistem. [Discuție](https://github.com/libsdl-org/SDL/issues/15799#issuecomment-4687665756).

- [ ] [#15740 — SDL\_ShowOpenFileDialog triggers SDL\_IsMainThread\_REAL() assertion on Linux/Wayland when using zenity](https://github.com/libsdl-org/SDL/issues/15740)
  - **Motiv:** Crash/assert sau lifecycle invalid raportat; reproducere și verificarea condițiilor de activare.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2026-06-04 19:01:27 UTC.

- [ ] [#15705 — Audio stutter/echo in Team Fortress 2 when using pipewire audio backend](https://github.com/libsdl-org/SDL/issues/15705)
  - **Motiv:** Degradare severă de CPU/audio raportată pe calea uzuală; verificați măsurătorile și versiunea/backportul.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-08-01 16:07:26 UTC.

- [ ] [#15603 — SDL 3.4.8: Access violation when quitting app on Xbox Series / Xbox One (GDK) -\> D3D12\_INTERNAL\_AcquireSwapchainTexture crash](https://github.com/libsdl-org/SDL/issues/15603)
  - **Motiv:** Crash/assert sau lifecycle invalid raportat; reproducere și verificarea condițiilor de activare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-11 14:17:00 UTC.

- [ ] [#15582 — zenity dialog has a race condition and only sometimes works](https://github.com/libsdl-org/SDL/issues/15582)
  - **Motiv:** Race raportat în dialogul zenity, cu pierderea rezultatului; reproducere deterministă și analiză de I/O.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 19:25:49 UTC.

- [ ] [#15570 — SDL\_GetAndroidExternalStoragePath SIGABRT](https://github.com/libsdl-org/SDL/issues/15570)
  - **Motiv:** Crash/assert sau lifecycle invalid raportat; reproducere și verificarea condițiilor de activare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-17 04:15:55 UTC.

- [ ] [#15507 — android: SDL3/SDL\_StartTextInput not working after pressing the down arrow button](https://github.com/libsdl-org/SDL/issues/15507)
  - **Motiv:** Regresie sau defect care împiedică inputul/afișarea/accesibilitatea în scenariul afectat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 19:21:29 UTC.

- [ ] [#15494 — SteamLink (Windows) Client crashes on a host when various sounds are triggered in the host machine.](https://github.com/libsdl-org/SDL/issues/15494)
  - **Motiv:** Crash sau concurență nesigură raportată; ownership și reproducere încă de verificat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 19:44:03 UTC.

- [ ] [#15448 — SDL D3D11 render multiple borderless windows crash on maximize or resize when NVIDIA Smooth Motion / AI Frame Generation is enabled](https://github.com/libsdl-org/SDL/issues/15448)
  - **Motiv:** Crash sau concurență nesigură raportată; ownership și reproducere încă de verificat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-25 14:53:21 UTC.

- [ ] [#15438 — iOS: Text input with hardware keyboard is broken](https://github.com/libsdl-org/SDL/issues/15438)
  - **Motiv:** Date text, aliniere sau contract GPU incorect raportat; verificați siguranța și paritatea backendurilor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-04-27 17:23:33 UTC.

- [ ] [#15422 — Brittle implicit alignment assumptions in Steam Controller driver](https://github.com/libsdl-org/SDL/issues/15422)
  - **Motiv:** Date text, aliniere sau contract GPU incorect raportat; verificați siguranța și paritatea backendurilor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-20 19:13:19 UTC.

- [ ] [#15380 — SDL\_WaitEventTimeout can block indefinitely on Wayland](https://github.com/libsdl-org/SDL/issues/15380)
  - **Motiv:** Blocare/timeout raportat, inclusiv pe căi de evenimente sau sincronizare; reproduceți cu prioritate.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-08-11 05:14:20 UTC.

- [ ] [#15348 — Discrepancy between D3D12 and Vulkan when uploading small block compressed textures](https://github.com/libsdl-org/SDL/issues/15348)
  - **Motiv:** Date text, aliniere sau contract GPU incorect raportat; verificați siguranța și paritatea backendurilor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 19:09:30 UTC.

- [ ] [#15346 — Intermittent test failures in 3.4.4: testrwlock timing out](https://github.com/libsdl-org/SDL/issues/15346)
  - **Motiv:** Blocare/timeout raportat, inclusiv pe căi de evenimente sau sincronizare; reproduceți cu prioritate.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 20:04:52 UTC.

- [ ] [#15293 — 8BitDo Controllers get blocked by Steam Input (Steam Overlay) when launching a SDL3.4.0+ app/program](https://github.com/libsdl-org/SDL/issues/15293)
  - **Motiv:** Regresie sau defect care împiedică inputul/afișarea/accesibilitatea în scenariul afectat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 20:32:44 UTC.

- [ ] [#15284 — SDL3 pen pressure and proximity issues on Linux when using evdev drivers in X11](https://github.com/libsdl-org/SDL/issues/15284)
  - **Motiv:** Regresie sau defect care împiedică inputul/afișarea/accesibilitatea în scenariul afectat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 20:33:34 UTC.

- [ ] [#15261 — macos: Raw mouse button events clash](https://github.com/libsdl-org/SDL/issues/15261)
  - **Motiv:** Regresie sau defect care împiedică inputul/afișarea/accesibilitatea în scenariul afectat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 20:34:08 UTC.

- [ ] [#15241 — SDL 3 GPU silently fails if threadgroup size is too large (Metal)](https://github.com/libsdl-org/SDL/issues/15241)
  - **Motiv:** Date text, aliniere sau contract GPU incorect raportat; verificați siguranța și paritatea backendurilor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-23 23:15:49 UTC.

- [ ] [#15214 — Segmentation fault in VULKAN\_SetCopyState](https://github.com/libsdl-org/SDL/issues/15214)
  - **Motiv:** Crash sau concurență nesigură raportată; ownership și reproducere încă de verificat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-09-04 22:50:34 UTC.

- [ ] [#15208 — SDL\_GetWindowSurface stucks on "Window framebuffer support not available" after trying to create software texture](https://github.com/libsdl-org/SDL/issues/15208)
  - **Motiv:** Regresie sau defect care împiedică inputul/afișarea/accesibilitatea în scenariul afectat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 18:58:39 UTC.

- [ ] [#15193 — macOS Dictation does not activate in SDL3 applications](https://github.com/libsdl-org/SDL/issues/15193)
  - **Motiv:** Regresie sau defect care împiedică inputul/afișarea/accesibilitatea în scenariul afectat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 18:48:01 UTC.

- [ ] [#15169 — iOS: MessageBoxes freezing the application.](https://github.com/libsdl-org/SDL/issues/15169)
  - **Motiv:** Blocare/timeout raportat, inclusiv pe căi de evenimente sau sincronizare; reproduceți cu prioritate.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 18:45:09 UTC.

- [ ] [#15148 — Android / SDL2: may not be threadsafe with Renderer Target](https://github.com/libsdl-org/SDL/issues/15148)
  - **Motiv:** Crash sau concurență nesigură raportată; ownership și reproducere încă de verificat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-17 04:24:22 UTC.

- [ ] [#15094 — SDL2 -\> SDL3 regression when handling touch events on X11](https://github.com/libsdl-org/SDL/issues/15094)
  - **Motiv:** Input/concurență sau sincronizare GPU incorectă raportată; verificați contractul și ordinea evenimentelor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-09 18:29:06 UTC.

- [ ] [#15085 — Camera: Magewell Pro Capture HDMI causes OOM on Linux](https://github.com/libsdl-org/SDL/issues/15085)
  - **Motiv:** Crash, OOM, use-after-free sau blocare raportată; investigație prioritară, fără reproducere locală.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 18:36:44 UTC.

- [ ] [#15081 — \`render\_testColorspaceLinear\` fails for vulkan renderer in x11](https://github.com/libsdl-org/SDL/issues/15081)
  - **Motiv:** Test/raport de rezultate grafice incorecte; conformance și identificarea backendului responsabil.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-22 03:40:42 UTC.

- [ ] [#15075 — Deadlock in \`OpenPhysicalAudioDevice\` for Pipewire backend on Linux](https://github.com/libsdl-org/SDL/issues/15075)
  - **Motiv:** Rămâne un scenariu public de blocare la deschiderea audio fără WirePlumber, distinct de diagnosticul inițial retras.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-27 18:15:20 UTC.
  - **Context:** Autorul inițial atribuie ulterior propria manifestare randării ImGui; alt participant oferă un reproducător separat pentru așteptarea PipeWire. Nu unificați cauzele. [Discuție](https://github.com/libsdl-org/SDL/issues/15075#issuecomment-5095046853).

- [ ] [#15010 — \`SDL\_SetMainReady\` gets called too early on Android, breaking \`SDL\_IsMainThread\`.](https://github.com/libsdl-org/SDL/issues/15010)
  - **Motiv:** Input/concurență sau sincronizare GPU incorectă raportată; verificați contractul și ordinea evenimentelor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-02-09 19:44:15 UTC.

- [ ] [#14973 — 2D rendering memory leak](https://github.com/libsdl-org/SDL/issues/14973)
  - **Motiv:** Leak de memorie/reservări raportat; verificați dimensiunea, repetabilitatea și ownership-ul SDL versus driver.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-09 19:01:50 UTC.

- [ ] [#14947 — Touchscreen, wrong finger motion coordinates when using kmsdrm backend](https://github.com/libsdl-org/SDL/issues/14947)
  - **Motiv:** Input/concurență sau sincronizare GPU incorectă raportată; verificați contractul și ordinea evenimentelor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-02 17:10:06 UTC.

- [ ] [#14941 — SDL\_GetClipboardText can return NULL upon SDL\_strdup("") failure, unlike the documentation suggests](https://github.com/libsdl-org/SDL/issues/14941)
  - **Motiv:** Contractul documentat poate ascunde un rezultat NULL la OOM; verificați riscul de dereferențiere în consumatori.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-08-23 14:06:12 UTC.

- [ ] [#14926 — SDL\_GetRelativeMouseState (SDL2 2.32.4, SDL3 3.2.10) returns absolute position values from Xvnc/Xnest/Xepyhr X servers](https://github.com/libsdl-org/SDL/issues/14926)
  - **Motiv:** Input/concurență sau sincronizare GPU incorectă raportată; verificați contractul și ordinea evenimentelor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-05 16:28:40 UTC.

- [ ] [#14925 — Android: move any native SDL code from SDLActivity to C thread](https://github.com/libsdl-org/SDL/issues/14925)
  - **Motiv:** Input/concurență sau sincronizare GPU incorectă raportată; verificați contractul și ordinea evenimentelor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-02-08 16:56:10 UTC.

- [ ] [#14914 — Virtual memory reservation leak in SDL\_GPU Vulkan backend with SPIR-V only initialization](https://github.com/libsdl-org/SDL/issues/14914)
  - **Motiv:** Leak de memorie/reservări raportat; verificați dimensiunea, repetabilitatea și ownership-ul SDL versus driver.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-29 22:17:07 UTC.

- [ ] [#14910 — Switch controller plugged in causes very long startup on Linux](https://github.com/libsdl-org/SDL/issues/14910)
  - **Motiv:** Pornire întârziată cu aproape două minute în raport; investigați blocarea detectării dispozitivelor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-28 22:17:38 UTC.

- [ ] [#14856 — Use-after-free in audio device cleanup (regression in 3.4.0)](https://github.com/libsdl-org/SDL/issues/14856)
  - **Motiv:** Crash de cleanup audio raportat; verificați obligatoriu dacă fixul similar din main îl elimină.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2026-06-30 20:32:24 UTC.
  - **Context:** Maintainerul solicită retestare după un fix posibil înrudit, fără să confirme că este aceeași problemă. [Discuție](https://github.com/libsdl-org/SDL/issues/14856#issuecomment-4847676723).

- [ ] [#14820 — torturethread segfaulting on arm64](https://github.com/libsdl-org/SDL/issues/14820)
  - **Motiv:** Crash, OOM, use-after-free sau blocare raportată; investigație prioritară, fără reproducere locală.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 22:44:15 UTC.

- [ ] [#14754 — GPU: Vulkan missing/incorrect barrier for INDIRECT argument buffer written by compute then consumed by vkCmdDrawIndexedIndirect](https://github.com/libsdl-org/SDL/issues/14754)
  - **Motiv:** Input/concurență sau sincronizare GPU incorectă raportată; verificați contractul și ordinea evenimentelor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-23 21:12:06 UTC.

- [ ] [#14722 — Alpha mod has no effect  for textures with SDL\_BLENDMODE\_BLEND\_PREMULTIPLIED](https://github.com/libsdl-org/SDL/issues/14722)
  - **Motiv:** Test/raport de rezultate grafice incorecte; conformance și identificarea backendului responsabil.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-29 19:03:58 UTC.

- [ ] [#14709 — SDL\_SetGPURenderStateFragmentUniforms() should verify that slot\_index is \<= RenderState's num\_uniform\_buffers?](https://github.com/libsdl-org/SDL/issues/14709)
  - **Motiv:** Crash, OOM, use-after-free sau blocare raportată; investigație prioritară, fără reproducere locală.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-23 21:13:57 UTC.

- [ ] [#14476 — SDL\_Renderer Vulkan issues with Android](https://github.com/libsdl-org/SDL/issues/14476)
  - **Motiv:** Randare sau format de pixeli incorect raportat pe funcționalitate existentă; conformance necesar.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-11-17 08:09:17 UTC.

- [ ] [#14450 — Accessibility issues in input boxes on mobile](https://github.com/libsdl-org/SDL/issues/14450)
  - **Motiv:** Funcție principală de input/afișare/accesibilitate indisponibilă în scenariul raportat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-11-12 17:32:29 UTC.

- [ ] [#14294 — Aggressive Gamepad blacklisting logic causes some genuine gamepads to be detected as keyboards](https://github.com/libsdl-org/SDL/issues/14294)
  - **Motiv:** Funcție principală de input/afișare/accesibilitate indisponibilă în scenariul raportat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-07-25 17:41:32 UTC.

- [ ] [#14251 — Android: issues when onDestroy() is called while application is running.](https://github.com/libsdl-org/SDL/issues/14251)
  - **Motiv:** Crash, lifecycle sau concurență nesigură raportată; verificați versiunea și ownership-ul SDL/OS/driver.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-16 16:28:33 UTC.

- [ ] [#14229 — \[SDL3\]: Cocoa crashes on resize after setting the window's aspect ratio aspects to (0, 0) manually](https://github.com/libsdl-org/SDL/issues/14229)
  - **Motiv:** Crash, lifecycle sau concurență nesigură raportată; verificați versiunea și ownership-ul SDL/OS/driver.
  - **GitHub:** OPEN · Etichete: `notourbug` · Milestone: `3.x` · Actualizat: 2025-10-25 23:01:06 UTC.

- [ ] [#14173 — Android / SDL\_Renderer Vulkan : background / foreground produce a black screen.](https://github.com/libsdl-org/SDL/issues/14173)
  - **Motiv:** Funcție principală de input/afișare/accesibilitate indisponibilă în scenariul raportat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-13 15:20:39 UTC.

- [ ] [#14171 — Android / SDL\_GPU not working with Android 16KB pages images.](https://github.com/libsdl-org/SDL/issues/14171)
  - **Motiv:** Crash, lifecycle sau concurență nesigură raportată; verificați versiunea și ownership-ul SDL/OS/driver.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-09 05:22:46 UTC.

- [ ] [#14164 — Potentially incorrect pixel format mappings on Android?](https://github.com/libsdl-org/SDL/issues/14164)
  - **Motiv:** Randare sau format de pixeli incorect raportat pe funcționalitate existentă; conformance necesar.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-17 04:09:17 UTC.

- [ ] [#13988 — Windows: SDL\_StartTextInput and SDL\_StopTextInput not work with second SDL\_Window.](https://github.com/libsdl-org/SDL/issues/13988)
  - **Motiv:** Funcție principală de input/afișare/accesibilitate indisponibilă în scenariul raportat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-03 20:24:21 UTC.

- [ ] [#13944 — iOS: SDL\_SetRenderLogicalPresentation(..., SDL\_LOGICAL\_PRESENTATION\_OVERSCAN, ...) behaves like LETTERBOX (adds bars) instead of overscan](https://github.com/libsdl-org/SDL/issues/13944)
  - **Motiv:** Randare sau format de pixeli incorect raportat pe funcționalitate existentă; conformance necesar.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 15:58:34 UTC.

- [ ] [#13920 — SDL2 window sometimes fails to gain input focus on macOS at startup](https://github.com/libsdl-org/SDL/issues/13920)
  - **Motiv:** Funcție principală de input/afișare/accesibilitate indisponibilă în scenariul raportat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-14 04:05:47 UTC.

- [ ] [#13806 — Thread safe initialization](https://github.com/libsdl-org/SDL/issues/13806)
  - **Motiv:** Crash, lifecycle sau concurență nesigură raportată; verificați versiunea și ownership-ul SDL/OS/driver.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 13:51:32 UTC.

- [ ] [#13792 — SDL2/3 + x11 + kwin: Kwin crashes on SDL\_CreateWindowWithProperties](https://github.com/libsdl-org/SDL/issues/13792)
  - **Motiv:** Crash, lifecycle sau concurență nesigură raportată; verificați versiunea și ownership-ul SDL/OS/driver.
  - **GitHub:** OPEN · Etichete: `notourbug` · Milestone: `3.x` · Actualizat: 2025-09-02 15:33:29 UTC.

- [ ] [#13777 — SDL3 on windows may got keyboard message with a windowID of 0](https://github.com/libsdl-org/SDL/issues/13777)
  - **Motiv:** Input, clipboard sau afișare indisponibilă în scenariul raportat; verificați regresia și condițiile de activare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-16 04:09:22 UTC.

- [ ] [#13775 — SDL\_dbus handling has a ton of null pointer crash locations if I'm not mistaken](https://github.com/libsdl-org/SDL/issues/13775)
  - **Motiv:** Acces NULL/crash sau threading nesigur raportat ori suspectat; verificare prioritară, nu cauză confirmată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-28 11:40:02 UTC.

- [ ] [#13737 — SDL\_HasClipboardText and SDL\_GetClipboardText fail on macOS](https://github.com/libsdl-org/SDL/issues/13737)
  - **Motiv:** Input, clipboard sau afișare indisponibilă în scenariul raportat; verificați regresia și condițiile de activare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2025-11-14 04:51:05 UTC.

- [ ] [#13733 — \[Windows\]Vulkan and OpenGL not presenting into WxPanel surface, unless drivers DXGI presentation hack used.](https://github.com/libsdl-org/SDL/issues/13733)
  - **Motiv:** Input, clipboard sau afișare indisponibilă în scenariul raportat; verificați regresia și condițiile de activare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-12 14:44:26 UTC.

- [ ] [#13705 — 2.26 KMSDRM: RPi5 DSI display, fails without device index hint](https://github.com/libsdl-org/SDL/issues/13705)
  - **Motiv:** Input, clipboard sau afișare indisponibilă în scenariul raportat; verificați regresia și condițiile de activare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-08 17:42:46 UTC.

- [ ] [#13284 — SDL\_RenderTextureRotated no longer displays texture](https://github.com/libsdl-org/SDL/issues/13284)
  - **Motiv:** Input, clipboard sau afișare indisponibilă în scenariul raportat; verificați regresia și condițiile de activare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-11-11 01:44:15 UTC.

- [ ] [#13279 — SDL3 iOS callback system shows black screen outside debugger (works in debugger)](https://github.com/libsdl-org/SDL/issues/13279)
  - **Motiv:** Input, clipboard sau afișare indisponibilă în scenariul raportat; verificați regresia și condițiile de activare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-08 17:36:20 UTC.

- [ ] [#13271 — \[macOS\] Subsequent SDL\_CreateTexture() calls have inconsistent behavior](https://github.com/libsdl-org/SDL/issues/13271)
  - **Motiv:** Rezultate vizuale ori I/O incorecte raportate; verificați contractul înainte de fix.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2025-10-08 17:43:21 UTC.

- [ ] [#13232 — When SDL\_HINT\_FORCE\_RAISEWINDOW is set to "1", SDL does not generate any SDL\_EVENT\_WINDOW\_FOCUS\_GAINED events.](https://github.com/libsdl-org/SDL/issues/13232)
  - **Motiv:** Input, clipboard sau afișare indisponibilă în scenariul raportat; verificați regresia și condițiile de activare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-28 17:33:26 UTC.

- [ ] [#13177 — Failure to detect Xbox Series Controller inputs after reconnection](https://github.com/libsdl-org/SDL/issues/13177)
  - **Motiv:** Input, clipboard sau afișare indisponibilă în scenariul raportat; verificați regresia și condițiile de activare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-08-07 20:52:44 UTC.

- [ ] [#13153 — Segfault when X11 forwarding](https://github.com/libsdl-org/SDL/issues/13153)
  - **Motiv:** Acces NULL/crash sau threading nesigur raportat ori suspectat; verificare prioritară, nu cauză confirmată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 15:13:53 UTC.

- [ ] [#13076 — \[SDL2/3\] \[Windows 10\] Window backbuffer getting incorrectly offset after secondary display resolution change](https://github.com/libsdl-org/SDL/issues/13076)
  - **Motiv:** Rezultate vizuale ori I/O incorecte raportate; verificați contractul înainte de fix.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-08 01:40:49 UTC.

- [ ] [#13054 — SDL3: Rendering Stops When Resizing Window with SDL\_WINDOW\_RESIZABLE Flag Beyond Certain Dimensions](https://github.com/libsdl-org/SDL/issues/13054)
  - **Motiv:** Input, clipboard sau afișare indisponibilă în scenariul raportat; verificați regresia și condițiile de activare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-16 00:27:11 UTC.

- [ ] [#13018 — SDL GPU: Crash when using textures and buffers on the same shader](https://github.com/libsdl-org/SDL/issues/13018)
  - **Motiv:** Acces NULL/crash sau threading nesigur raportat ori suspectat; verificare prioritară, nu cauză confirmată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 16:03:31 UTC.

- [ ] [#13001 — Vulkan: Fully using a CPU thread with vsync on](https://github.com/libsdl-org/SDL/issues/13001)
  - **Motiv:** Blocaje de ordinul secundelor sau ocuparea integrală a unui thread raportate; măsurați și verificați ownership-ul extern.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-05-11 17:31:33 UTC.

- [ ] [#12943 — Message boxes on background threads...](https://github.com/libsdl-org/SDL/issues/12943)
  - **Motiv:** Acces NULL/crash sau threading nesigur raportat ori suspectat; verificare prioritară, nu cauză confirmată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-05-27 02:19:37 UTC.

- [ ] [#12936 — SDL\_ReadIO isn't reading PNGs properly on Android](https://github.com/libsdl-org/SDL/issues/12936)
  - **Motiv:** Rezultate vizuale ori I/O incorecte raportate; verificați contractul înainte de fix.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-05-08 12:34:44 UTC.

- [ ] [#12920 — When using multiple keyboards and raw input, a KEY\_UP event is lost if the keys are released together](https://github.com/libsdl-org/SDL/issues/12920)
  - **Motiv:** Pierdere de input, blocare sau imposibilitate de afișare raportată; investigație funcțională prioritară.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-11-12 19:52:40 UTC.

- [ ] [#12750 — Window mouse drag resize stalling app on windows when text input started and borderless style is set.](https://github.com/libsdl-org/SDL/issues/12750)
  - **Motiv:** Pierdere de input, blocare sau imposibilitate de afișare raportată; investigație funcțională prioritară.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2026-03-24 13:10:22 UTC.

- [ ] [#12745 — \[SDL3\] Window used in plugin as child of host will lose mouse events on macOS](https://github.com/libsdl-org/SDL/issues/12745)
  - **Motiv:** Pierdere de input, blocare sau imposibilitate de afișare raportată; investigație funcțională prioritară.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-05-22 09:56:38 UTC.

- [ ] [#12734 — hidapi gamepad device lost on suspend (steamdeck)](https://github.com/libsdl-org/SDL/issues/12734)
  - **Motiv:** Pierdere de input, blocare sau imposibilitate de afișare raportată; investigație funcțională prioritară.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-14 19:33:38 UTC.

- [ ] [#12727 — Render texture null to null but only left top was filled in Direct3D12](https://github.com/libsdl-org/SDL/issues/12727)
  - **Motiv:** Randare sau utilizare GPU invalidă raportată; verificați contractul și diferențele de backend.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-23 22:52:03 UTC.

- [ ] [#12715 — \[SDL GPU\] SDL\_GPU\_PRESENTMODE\_IMMEDIATE with SDL\_WINDOW\_HIGH\_PIXEL\_DENSITY causes macOS crash on 120hz monitor](https://github.com/libsdl-org/SDL/issues/12715)
  - **Motiv:** Crash/reboot de sistem raportat pe o combinație de display și Metal; retestare hardware prioritară.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-23 22:57:07 UTC.
  - **Context:** Autorul a trimis un raport Apple și consideră posibil un defect OS; nu atribuiți automat cauza SDL. [Discuție](https://github.com/libsdl-org/SDL/issues/12715#issuecomment-2777107253).

- [ ] [#12660 — InterruptionBegin (in SDL3) (SDL\_coreaudio.m:344)](https://github.com/libsdl-org/SDL/issues/12660)
  - **Motiv:** Crash sau blocare de sistem raportată; verificați reproducerea și responsabilitatea SDL/driverului.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2025-05-02 17:31:07 UTC.

- [ ] [#12656 — 3.2.8, Direct3d11 screen corruption.](https://github.com/libsdl-org/SDL/issues/12656)
  - **Motiv:** Randare sau utilizare GPU invalidă raportată; verificați contractul și diferențele de backend.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 15:51:49 UTC.

- [ ] [#12613 — kmsdrm window receives no mouse/keyboard events](https://github.com/libsdl-org/SDL/issues/12613)
  - **Motiv:** Pierdere de input, blocare sau imposibilitate de afișare raportată; investigație funcțională prioritară.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 15:53:01 UTC.

- [ ] [#12560 — \[SDL3\] \`SDL\_Convert\_F32\_to\_S16\_NEON\` doesn't handle overflows](https://github.com/libsdl-org/SDL/issues/12560)
  - **Motiv:** Crash sau blocare de sistem raportată; verificați reproducerea și responsabilitatea SDL/driverului.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 22:08:50 UTC.

- [ ] [#12539 — Please respect minImageCount even for MAILBOX](https://github.com/libsdl-org/SDL/issues/12539)
  - **Motiv:** Randare sau utilizare GPU invalidă raportată; verificați contractul și diferențele de backend.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-16 21:32:10 UTC.

- [ ] [#12487 — SDL\_UploadToGPUTexture fails to upload Cubemap data on vulkan backend](https://github.com/libsdl-org/SDL/issues/12487)
  - **Motiv:** Randare sau utilizare GPU invalidă raportată; verificați contractul și diferențele de backend.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-23 21:16:24 UTC.

- [ ] [#12452 — SDL GPU (Metal) - scissor rect outside render boundaries can cause crash on iOS](https://github.com/libsdl-org/SDL/issues/12452)
  - **Motiv:** Crash sau blocare de sistem raportată; verificați reproducerea și responsabilitatea SDL/driverului.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-09 21:29:23 UTC.

- [ ] [#12419 — SDL-3.2.4 — silently fails for opening a window](https://github.com/libsdl-org/SDL/issues/12419)
  - **Motiv:** Pierdere de input, blocare sau imposibilitate de afișare raportată; investigație funcțională prioritară.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-18 17:59:29 UTC.

- [ ] [#12204 — Android ANR Native lock contention: SDL\_LockJoysticks (onNativePadDown) & native\_release\_interface](https://github.com/libsdl-org/SDL/issues/12204)
  - **Motiv:** Crash, deadlock sau ANR raportat; reproduceți și separați defectul SDL de driver/OS/utilizare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-09-06 17:37:42 UTC.

- [ ] [#12200 — SDL GPU: GPUBuffers have their StructureByteStride set to 0 on DX12 which breaks StructuredBuffers reads on AMD GPU](https://github.com/libsdl-org/SDL/issues/12200)
  - **Motiv:** Acces GPU, rezultate sau tratarea inputului incompatibile cu contractul raportat; investigație prioritară.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-11-05 00:30:00 UTC.

- [ ] [#12141 — Macos: Rendering to an external NSView doesn't work in practice](https://github.com/libsdl-org/SDL/issues/12141)
  - **Motiv:** Acces GPU, rezultate sau tratarea inputului incompatibile cu contractul raportat; investigație prioritară.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-02 15:51:55 UTC.

- [ ] [#12053 — Crash when closing secondary window with Vulkan renderer on Linux w/ Wayland](https://github.com/libsdl-org/SDL/issues/12053)
  - **Motiv:** Crash, deadlock sau ANR raportat; reproduceți și separați defectul SDL de driver/OS/utilizare.
  - **GitHub:** OPEN · Etichete: `notourbug` · Milestone: `3.x` · Actualizat: 2025-01-22 15:30:13 UTC.

- [ ] [#11916 — SDL3 GPU: SDL\_DrawGPUIndexedPrimitivesIndirect sets instance count to 0?](https://github.com/libsdl-org/SDL/issues/11916)
  - **Motiv:** Acces GPU, rezultate sau tratarea inputului incompatibile cu contractul raportat; investigație prioritară.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-05-26 00:20:42 UTC.

- [ ] [#11843 — Windows pen handling invokes undefined behaviour](https://github.com/libsdl-org/SDL/issues/11843)
  - **Motiv:** Acces GPU, rezultate sau tratarea inputului incompatibile cu contractul raportat; investigație prioritară.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-07 15:24:34 UTC.

- [ ] [#11819 — SDL3: Camera example deadlocks application using V4L2 Capture Card](https://github.com/libsdl-org/SDL/issues/11819)
  - **Motiv:** Crash, deadlock sau ANR raportat; reproduceți și separați defectul SDL de driver/OS/utilizare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-05 11:08:00 UTC.

- [ ] [#11725 — SDL3, macOS: Crash when changing window size](https://github.com/libsdl-org/SDL/issues/11725)
  - **Motiv:** Crash, deadlock sau ANR raportat; reproduceți și separați defectul SDL de driver/OS/utilizare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-24 15:21:13 UTC.

- [ ] [#11673 — Crash in SDL\_hid\_enumerate on macOS 15.2](https://github.com/libsdl-org/SDL/issues/11673)
  - **Motiv:** Crash, deadlock sau ANR raportat; reproduceți și separați defectul SDL de driver/OS/utilizare.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-03 16:09:52 UTC.

- [ ] [#11552 — \[GPU\] SDL\_CreateGPUDevice crashes on X11 with Vulkan backend when using \`prime-run\` ](https://github.com/libsdl-org/SDL/issues/11552)
  - **Motiv:** Crash/OOM sau blocare indefinită raportată; reproduceți și identificați ownership-ul.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-27 03:11:03 UTC.

- [ ] [#11473 — SDL3: PipeWire's emulated V4L2 cameras never acquire a frame](https://github.com/libsdl-org/SDL/issues/11473)
  - **Motiv:** Dispozitivul/calea raportată împiedică pornirea sau funcția principală; verificați reproducerea.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-04 21:14:27 UTC.

- [ ] [#11461 — Amazon Luna Controller causing app not to launch](https://github.com/libsdl-org/SDL/issues/11461)
  - **Motiv:** Dispozitivul/calea raportată împiedică pornirea sau funcția principală; verificați reproducerea.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 19:52:36 UTC.

- [ ] [#11411 — Android SDL\_CreateSurface with massive w & h bombs horribly](https://github.com/libsdl-org/SDL/issues/11411)
  - **Motiv:** Crash/OOM sau blocare indefinită raportată; reproduceți și identificați ownership-ul.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-11-05 15:24:43 UTC.

- [ ] [#11407 — SDL\_GetDisplayUsableBounds returns initial bounds](https://github.com/libsdl-org/SDL/issues/11407)
  - **Motiv:** Date, stare GPU ori conversii incorecte raportate; verificarea contractului și a rezultatelor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 15:08:50 UTC.

- [ ] [#11363 — GPU: SDL\_BlitGPUTexture may overwrite fragment uniforms](https://github.com/libsdl-org/SDL/issues/11363)
  - **Motiv:** Date, stare GPU ori conversii incorecte raportate; verificarea contractului și a rezultatelor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-23 21:16:45 UTC.

- [ ] [#11343 — GPU: Integer Color Target Clears](https://github.com/libsdl-org/SDL/issues/11343)
  - **Motiv:** Date, stare GPU ori conversii incorecte raportate; verificarea contractului și a rezultatelor.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:51:45 UTC.

- [ ] [#11019 — application does not stop if not bound to internal sound card](https://github.com/libsdl-org/SDL/issues/11019)
  - **Motiv:** Crash/OOM sau blocare indefinită raportată; reproduceți și identificați ownership-ul.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 18:43:15 UTC.

- [ ] [#10918 — LD\_PROFILE/AUDIT cause crash with SDL\_VIDEODRIVER=wayland](https://github.com/libsdl-org/SDL/issues/10918)
  - **Motiv:** Crash/OOM sau blocare indefinită raportată; reproduceți și identificați ownership-ul.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 20:24:03 UTC.

- [ ] [#10877 — YUV: RGB to YUV results in wrong images](https://github.com/libsdl-org/SDL/issues/10877)
  - **Motiv:** Date, stare GPU ori conversii incorecte raportate; verificarea contractului și a rezultatelor.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2024-12-27 01:57:30 UTC.

- [ ] [#10842 — SDL\_Camera intermittently hangs on CloseCamera when using Pipewire backend](https://github.com/libsdl-org/SDL/issues/10842)
  - **Motiv:** Crash/OOM sau blocare indefinită raportată; reproduceți și identificați ownership-ul.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-04 21:15:57 UTC.

- [ ] [#10309 — SDL3 SDL\_Init crash on ios 15](https://github.com/libsdl-org/SDL/issues/10309)
  - **Motiv:** Crash sau blocare raportată; reproducere și verificarea versiunii înainte de fix.
  - **GitHub:** OPEN · Etichete: `Apple` · Milestone: `3.x` · Actualizat: 2024-12-04 19:20:54 UTC.

- [ ] [#10279 — SDL\_Renderer vulkan backend fails while re-entering the app on android ](https://github.com/libsdl-org/SDL/issues/10279)
  - **Motiv:** Lifecycle, text, conversii sau afișare incorecte raportate; verificați contractul și regresia.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 21:22:52 UTC.

- [ ] [#10278 — Incorrect usage of GetStringUTFChars/NewStringUTF in android jni code](https://github.com/libsdl-org/SDL/issues/10278)
  - **Motiv:** Lifecycle, text, conversii sau afișare incorecte raportate; verificați contractul și regresia.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-20 17:55:25 UTC.

- [ ] [#10047 — Alt-Gr is broken again. ](https://github.com/libsdl-org/SDL/issues/10047)
  - **Motiv:** Lifecycle, text, conversii sau afișare incorecte raportate; verificați contractul și regresia.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 20:55:34 UTC.

- [ ] [#10031 — Issues with multiple opengl contexts on iOS](https://github.com/libsdl-org/SDL/issues/10031)
  - **Motiv:** Lifecycle, text, conversii sau afișare incorecte raportate; verificați contractul și regresia.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 19:22:55 UTC.

- [ ] [#9927 — SDL\_CreateWindowFrom handle leak](https://github.com/libsdl-org/SDL/issues/9927)
  - **Motiv:** Creștere continuă de resurse sau busy-loop raportat; verificați măsurătorile și ownership-ul.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:57:03 UTC.

- [ ] [#9859 — Cocoa\_StopTextInput causes a freeze](https://github.com/libsdl-org/SDL/issues/9859)
  - **Motiv:** Crash sau blocare raportată; reproducere și verificarea versiunii înainte de fix.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2024-12-21 16:21:16 UTC.

- [ ] [#9745 — SDLView resetCursorRects crash with (FFmpeg 7) ffplay](https://github.com/libsdl-org/SDL/issues/9745)
  - **Motiv:** Crash sau blocare raportată; reproducere și verificarea versiunii înainte de fix.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-11-26 02:01:14 UTC.

- [ ] [#9521 — Window surface is not invalidated if format changes](https://github.com/libsdl-org/SDL/issues/9521)
  - **Motiv:** Lifecycle, text, conversii sau afișare incorecte raportate; verificați contractul și regresia.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-20 03:45:24 UTC.

- [ ] [#9409 — Raw input related issues](https://github.com/libsdl-org/SDL/issues/9409)
  - **Motiv:** Creștere continuă de resurse sau busy-loop raportat; verificați măsurătorile și ownership-ul.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-05-17 20:11:17 UTC.

- [ ] [#9027 — Displaying the Android soft keyboard causes serious rendering issues when combined with controller input](https://github.com/libsdl-org/SDL/issues/9027)
  - **Motiv:** Lifecycle, text, conversii sau afișare incorecte raportate; verificați contractul și regresia.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `2.x` · Actualizat: 2026-08-05 14:31:19 UTC.

- [ ] [#8944 — Feature Request: Enhanced Keyboard Hook for Accessibility Compatibility with Screen Readers like JAWS](https://github.com/libsdl-org/SDL/issues/8944)
  - **Motiv:** Conflict cu screen reader care poate împiedica utilizarea aplicației; prioritate de accesibilitate, nu simplu polish.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-05-23 17:14:32 UTC.

- [ ] [#8883 — surface\_testCompleteSurfaceConversion:  runtime error: shift exponent 254 is too large for 32-bit type](https://github.com/libsdl-org/SDL/issues/8883)
  - **Motiv:** Lifecycle, text, conversii sau afișare incorecte raportate; verificați contractul și regresia.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:55:22 UTC.

- [ ] [#8843 — Switch Pro controller hangs in SDL\_InitJoysticks in SDL3](https://github.com/libsdl-org/SDL/issues/8843)
  - **Motiv:** Crash sau blocare raportată; reproducere și verificarea versiunii înainte de fix.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 17:35:04 UTC.

- [ ] [#8281 — Possible overflow in SDL\_SW\_UpdateYUVTexture](https://github.com/libsdl-org/SDL/issues/8281)
  - **Motiv:** Posibil overflow în dimensiunea copiei YUV; verificați limitele și accesul la memorie, fără vulnerabilitate confirmată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:37:00 UTC.

- [ ] [#8111 — \[x11\] events don't work in testnative](https://github.com/libsdl-org/SDL/issues/8111)
  - **Motiv:** Input absent sau rezultate de randare greșite raportate; verificați regresia și scenariul activ.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:33:42 UTC.

- [ ] [#8070 — First frame of metal renderer shows garbage](https://github.com/libsdl-org/SDL/issues/8070)
  - **Motiv:** Input absent sau rezultate de randare greșite raportate; verificați regresia și scenariul activ.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 17:04:50 UTC.

- [ ] [#7759 — \[Windows\] The xbox controllers do not respond if the computer has been remote controlled by the 'mstsc.exe'.](https://github.com/libsdl-org/SDL/issues/7759)
  - **Motiv:** Input absent sau rezultate de randare greșite raportate; verificați regresia și scenariul activ.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-04 09:00:52 UTC.

- [ ] [#6650 — ELAN touchpad does not generate mouse events](https://github.com/libsdl-org/SDL/issues/6650)
  - **Motiv:** Input absent sau rezultate de randare greșite raportate; verificați regresia și scenariul activ.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:04:15 UTC.

- [ ] [#6306 — Program handle leak.](https://github.com/libsdl-org/SDL/issues/6306)
  - **Motiv:** Leak de handles raportat; verificați creșterea resurselor și validitatea propunerii autorului.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2023-11-07 17:10:52 UTC.

- [ ] [#5949 — Viewport resets on window move](https://github.com/libsdl-org/SDL/issues/5949)
  - **Motiv:** Stare de afișare/input greșită raportată; verificați dacă problema istorică mai afectează versiunile curente.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-11-17 12:23:52 UTC.

- [ ] [#5128 — SDL doesn't handle clipboard when MessageBox is shown](https://github.com/libsdl-org/SDL/issues/5128)
  - **Motiv:** Blocare de evenimente/UI sau ANR raportat; verificați versiunea și scenariul înainte de fix.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-11-07 04:00:02 UTC.

- [ ] [#4398 — Multi-display configuration lost in linux when going fullscreen and then turning back](https://github.com/libsdl-org/SDL/issues/4398)
  - **Motiv:** Stare de afișare/input greșită raportată; verificați dacă problema istorică mai afectează versiunile curente.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-26 22:07:51 UTC.

- [ ] [#2921 — SDL\_StartTextInput() mangles Android joystick input](https://github.com/libsdl-org/SDL/issues/2921)
  - **Motiv:** Blocare de evenimente/UI sau ANR raportat; verificați versiunea și scenariul înainte de fix.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 17:05:41 UTC.

- [ ] [#2497 — Main thread gets stuck on left mouse down](https://github.com/libsdl-org/SDL/issues/2497)
  - **Motiv:** Blocare de evenimente/UI sau ANR raportat; verificați versiunea și scenariul înainte de fix.
  - **GitHub:** OPEN · Etichete: `Apple`, `early in milestone` · Milestone: `3.x` · Actualizat: 2023-03-07 00:49:35 UTC.

- [ ] [#1836 — SDL\_SetRelativeMouseMode causes xrel/yrel in SDL\_MOUSEMOTION to be large absolute values](https://github.com/libsdl-org/SDL/issues/1836)
  - **Motiv:** Stare de afișare/input greșită raportată; verificați dacă problema istorică mai afectează versiunile curente.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-11-22 02:48:31 UTC.

## MEDIUM

- [ ] [#16261 — DS4 (Sony official dongle) set LED color regression (windows)](https://github.com/libsdl-org/SDL/issues/16261)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-09-07 05:46:53 UTC.

- [ ] [#16237 — \[Feature\]Betop Asura 2 SparkLink+ Pro: buttons and rumble work, but SDL gyro/accel is not detected (works in SDL2 and on real Switch)](https://github.com/libsdl-org/SDL/issues/16237)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-09-04 11:01:14 UTC.

- [ ] [#16233 — pen: Android vs proximity out](https://github.com/libsdl-org/SDL/issues/16233)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-09-02 16:00:30 UTC.

- [ ] [#16220 — Incorrect SDL3 mapping for PDP Faceoff Deluxe+ Switch Controller (0e6f:0184) on Linux](https://github.com/libsdl-org/SDL/issues/16220)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-08-31 01:56:14 UTC.

- [ ] [#16218 — wayland: SDL\_WINDOW\_NOT\_FOCUSABLE not honored on regular toplevels](https://github.com/libsdl-org/SDL/issues/16218)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-09-05 18:15:10 UTC.

- [ ] [#16216 — missing SDL\_PROP\_RENDERER\_CREATE\_GPU\_SHADERS\_\*\_BOOLEAN for DXBC, METALLIB, and PRIVATE](https://github.com/libsdl-org/SDL/issues/16216)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-09-01 11:59:59 UTC.

- [ ] [#16208 — Darwin keyboard key 95 may actually be International 6](https://github.com/libsdl-org/SDL/issues/16208)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-08-28 09:52:07 UTC.

- [ ] [#16204 — Unable to build project with cmake after cloning latest update.](https://github.com/libsdl-org/SDL/issues/16204)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.4.18` · Actualizat: 2026-09-03 16:27:54 UTC.

- [ ] [#16203 — Metal: "Resource has the wrong storage mode set"](https://github.com/libsdl-org/SDL/issues/16203)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-26 17:26:00 UTC.

- [ ] [#16192 — Cannot resize a wayland window after snapping it to the side on GNOME](https://github.com/libsdl-org/SDL/issues/16192)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `notourbug` · Milestone: — · Actualizat: 2026-08-27 19:20:27 UTC.

- [ ] [#16191 — KMSDRM undesirable video mode change](https://github.com/libsdl-org/SDL/issues/16191)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-25 00:38:21 UTC.

- [ ] [#16189 — GameSir-G7 Pro 8K: the right joystick does not work properly when holding LB](https://github.com/libsdl-org/SDL/issues/16189)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-23 17:12:30 UTC.

- [ ] [#16187 — Flydigi Vader 5 Pro rumble does not work — rumble path missed by the unnumbered-report fix in #15594](https://github.com/libsdl-org/SDL/issues/16187)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-23 17:01:21 UTC.

- [ ] [#16177 — SDL3 Process API Enhacements](https://github.com/libsdl-org/SDL/issues/16177)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-08-21 22:20:55 UTC.

- [ ] [#16172 — CMake cannot find X11 dependencies](https://github.com/libsdl-org/SDL/issues/16172)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-08-20 10:52:45 UTC.

- [ ] [#16160 — SDL incorrectly attributes screensaver inhibition to the wrong application](https://github.com/libsdl-org/SDL/issues/16160)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-22 15:33:53 UTC.

- [ ] [#16144 — Wayland: SDL\_HasClipboardData() and SDL\_GetClipboardData() disagree (conformance vs exact UTI match)](https://github.com/libsdl-org/SDL/issues/16144)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-08-31 16:08:34 UTC.

- [ ] [#16121 — \`SDL\_VideoInit()\` unconditionally fails when the selected video backend reports zero displays](https://github.com/libsdl-org/SDL/issues/16121)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-06 15:42:14 UTC.

- [ ] [#16086 — testyuv --all fails BT.2020 conversion tests](https://github.com/libsdl-org/SDL/issues/16086)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-30 23:44:01 UTC.

- [ ] [#16068 — Windows: window HDR properties don't update when the SDR white level changes or the window moves to another display](https://github.com/libsdl-org/SDL/issues/16068)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-27 20:03:53 UTC.

- [ ] [#16065 — haiku: system numlock state not properly tracked during application lifetime](https://github.com/libsdl-org/SDL/issues/16065)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-07-27 14:43:11 UTC.

- [ ] [#16063 — Windows 11: SDL\_GetDisplayContentScale() returns incorrect scale value for \`"unaware"\` DPI awareness](https://github.com/libsdl-org/SDL/issues/16063)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-07-30 11:50:38 UTC.

- [ ] [#16058 — Wayland: let a client declare border insets](https://github.com/libsdl-org/SDL/issues/16058)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-03 08:13:44 UTC.

- [ ] [#16047 — Some media keys (e.g. "mail") don't appear to be recognised properly as distinct keys](https://github.com/libsdl-org/SDL/issues/16047)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-25 11:30:22 UTC.

- [ ] [#16043 — GPU: D3D12 HDR\_EXTENDED\_LINEAR swapchain composition is unreachable](https://github.com/libsdl-org/SDL/issues/16043)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-07-26 17:41:25 UTC.

- [ ] [#15987 — \[wayland - zwp\_text\_input\_v3\] - \`delete\_surrounding\_text\` event not handled](https://github.com/libsdl-org/SDL/issues/15987)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-26 20:10:59 UTC.

- [ ] [#15972 — \`SDL\_GamepadHasSensor\` Axis orientation between Controller and Handhelds](https://github.com/libsdl-org/SDL/issues/15972)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-07-11 04:56:10 UTC.

- [ ] [#15967 — macOS 26: stale mouse motion positions when the cursor crosses a window edge after a focus change (windowed mode)](https://github.com/libsdl-org/SDL/issues/15967)
  - **Motiv:** Rămân coordonate mouse suspecte la nivel macOS; nu considerați toate manifestările din fir încă active.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.4.18` · Actualizat: 2026-09-02 10:33:43 UTC.
  - **Context:** O reproducere înrudită nu mai apare pe main; maintainerul a separat fixul urgent de întrebarea rămasă. [Discuție](https://github.com/libsdl-org/SDL/issues/15967#issuecomment-5495701617).

- [ ] [#15955 — Trackpad handling](https://github.com/libsdl-org/SDL/issues/15955)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-08 16:22:13 UTC.

- [ ] [#15946 — SDL\_GPU: SDL\_GPUVulkanOptions::feature\_list direct contents ignored](https://github.com/libsdl-org/SDL/issues/15946)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-03 17:56:20 UTC.

- [ ] [#15897 — Plasma Keyboard 6.7 + SDL\_StartTextInput breaks SDL\_EVENT\_KEY\_DOWN for text keys.](https://github.com/libsdl-org/SDL/issues/15897)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `notourbug` · Milestone: `3.x` · Actualizat: 2026-06-29 21:54:36 UTC.

- [ ] [#15885 — Texture quality degradation in CS2 on Wayland (NVIDIA), SDL 3.5.0, SDL\_VIDEODRIVER=x11 workaround prevents it](https://github.com/libsdl-org/SDL/issues/15885)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-06-24 21:39:02 UTC.

- [ ] [#15870 — Add platforms to test matrix if specific files are changed](https://github.com/libsdl-org/SDL/issues/15870)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-22 16:50:59 UTC.

- [ ] [#15850 — No display event fired when switching between desktop and exclusive fullscreen](https://github.com/libsdl-org/SDL/issues/15850)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-18 03:16:40 UTC.

- [ ] [#15829 — GPU driver performance](https://github.com/libsdl-org/SDL/issues/15829)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-07-26 20:29:22 UTC.

- [ ] [#15807 — macOS: Korean IME: first keystroke after IME activation is committed as raw jamo instead of starting composition](https://github.com/libsdl-org/SDL/issues/15807)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-26 20:29:53 UTC.

- [ ] [#15773 — Video: Bottom black bar. Call SetWindowSize when SDL\_EVENT\_WINDOW\_EXPOSED, live resize window on Windows](https://github.com/libsdl-org/SDL/issues/15773)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 20:18:16 UTC.

- [ ] [#15764 — Confusing audio buffer size calculation](https://github.com/libsdl-org/SDL/issues/15764)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 20:19:48 UTC.

- [ ] [#15762 — Strange behavior of SDL\_BlitSurface](https://github.com/libsdl-org/SDL/issues/15762)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-16 20:47:07 UTC.

- [ ] [#15751 — \[Windows\] Window Transparency Issue with Layering Over DXGI Swapchain](https://github.com/libsdl-org/SDL/issues/15751)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-17 04:08:19 UTC.

- [ ] [#15713 — Potential bug with DualShock 4 light bar control: Conflicts between kernel-level settings and way SDL sets the color](https://github.com/libsdl-org/SDL/issues/15713)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-30 16:48:44 UTC.

- [ ] [#15684 — eglBindAPI triggers a hidden error during window creation on Angle](https://github.com/libsdl-org/SDL/issues/15684)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-10 02:18:24 UTC.

- [ ] [#15663 — DARWIN: virtual HID gamepad input works, but rumble isn't sent](https://github.com/libsdl-org/SDL/issues/15663)
  - **Motiv:** Rumble absent în versiunea SDL livrată de aplicație; retestare pe versiune nouă înainte de fix.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.6.0` · Actualizat: 2026-06-17 04:16:38 UTC.
  - **Context:** Autorul urmează să verifice dacă actualizarea PCSX2/SDL rezolvă cazul. [Discuție](https://github.com/libsdl-org/SDL/issues/15663#issuecomment-4723253931).

- [ ] [#15658 — 8BitDo Ultimate 2C Wireless - Triggers lack analog input](https://github.com/libsdl-org/SDL/issues/15658)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-29 15:51:11 UTC.

- [ ] [#15656 — SDL\_GPU: Opt-in low-latency presentation](https://github.com/libsdl-org/SDL/issues/15656)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 21:10:59 UTC.

- [ ] [#15638 — Touchpad Touch can cause jitter when adding a standalone Menu Cursor or Camera action](https://github.com/libsdl-org/SDL/issues/15638)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-29 11:15:19 UTC.

- [ ] [#15598 — cmake: libbsd linking weirdness on Linux](https://github.com/libsdl-org/SDL/issues/15598)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-15 03:25:43 UTC.

- [ ] [#15541 — \`SDL\_EnumerateDirectory\` doesn't parse android \`content://\` paths](https://github.com/libsdl-org/SDL/issues/15541)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-05-22 22:26:03 UTC.

- [ ] [#15525 — Problem transferring executable from Alpine to Mint](https://github.com/libsdl-org/SDL/issues/15525)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 20:26:47 UTC.

- [ ] [#15502 — Emscripten: Since SDL3 the canvas is being resized](https://github.com/libsdl-org/SDL/issues/15502)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-04 06:03:04 UTC.

- [ ] [#15498 — Ctrl-C doesn't work in win32 console app](https://github.com/libsdl-org/SDL/issues/15498)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-03 15:17:59 UTC.

- [ ] [#15497 — BEYEE Zero delay USB Encoders not recognised in ES-DE for Windows](https://github.com/libsdl-org/SDL/issues/15497)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-22 14:21:32 UTC.

- [ ] [#15490 — \`SDL\_CreateColorCursor\` does not support transparent surfaces](https://github.com/libsdl-org/SDL/issues/15490)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-01 17:42:56 UTC.

- [ ] [#15403 — Enumerate DirectInput devices in SDL\_JoystickThread (or have another hotplug thread for DirectInput)](https://github.com/libsdl-org/SDL/issues/15403)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-04-20 18:53:15 UTC.

- [ ] [#15371 — \[SDL 2.32\] OpenGL renderer causes corruption when drawing rounded rectangles with LVGL on AMD Radeon + Mesa 25.3.6](https://github.com/libsdl-org/SDL/issues/15371)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `endoflife`, `waiting` · Milestone: `2.x` · Actualizat: 2026-06-16 20:29:57 UTC.

- [ ] [#15345 — Crash seen in Team Fortress 2 with \`SDL\_AUDIODRIVER=alsa\` after switching from "classic" SDL 2.32.10 to sdl2-compat 2.32.64 + SDL 3.4.2](https://github.com/libsdl-org/SDL/issues/15345)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 20:31:39 UTC.

- [ ] [#15338 — Linux mouse input issues?](https://github.com/libsdl-org/SDL/issues/15338)
  - **Motiv:** Regresii de input urmărite în joc/compositor; atribuirea SDL nu este stabilită de discuția consultată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-28 02:40:55 UTC.
  - **Context:** Sunt discutate Niri, versiunea SDL livrată de joc și o reproducere în afara Niri; nu este o cauză unică confirmată. [Discuție](https://github.com/libsdl-org/SDL/issues/15338#issuecomment-4320946684).

- [ ] [#15324 — macOS: Hit testing is not performed for mouse right-click (SDL3)](https://github.com/libsdl-org/SDL/issues/15324)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-24 02:00:04 UTC.

- [ ] [#15323 — macOS: Mouse warps when leaving relative mode with multiple windows](https://github.com/libsdl-org/SDL/issues/15323)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 20:32:25 UTC.

- [ ] [#15303 — \[Bug\] \`/include/SDL3/SDL\_messagebox.h\` doesn't adhere to the \`system-ui\` \`font-family\`, nor \`org.freedesktop.appearance.color-scheme\`.](https://github.com/libsdl-org/SDL/issues/15303)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-02 21:31:38 UTC.

- [ ] [#15295 — Keymod state in SDL\_KeyboardEvent is out of sync.](https://github.com/libsdl-org/SDL/issues/15295)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `notourbug` · Milestone: `3.x` · Actualizat: 2026-04-02 18:02:01 UTC.

- [ ] [#15277 — SDL\_HINT\_MAIN\_CALLBACK\_RATE on iOS](https://github.com/libsdl-org/SDL/issues/15277)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-03-28 19:57:45 UTC.

- [ ] [#15273 — SDL3 macos full screen weirdness](https://github.com/libsdl-org/SDL/issues/15273)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 19:00:14 UTC.

- [ ] [#15259 — Multiple window resizing visual glitches](https://github.com/libsdl-org/SDL/issues/15259)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 20:34:23 UTC.

- [ ] [#15245 — Nintendo Switch 2 Pro Controller Does Not Work (Linux) SDL 3.4.2](https://github.com/libsdl-org/SDL/issues/15245)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-22 15:33:29 UTC.

- [ ] [#15242 — SDL2-compat/SDL3 invisible mouse cursor with KMSDRM](https://github.com/libsdl-org/SDL/issues/15242)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-15 16:41:48 UTC.

- [ ] [#15237 — Main callback rate drops to 64 calls per second when interacting with window borders](https://github.com/libsdl-org/SDL/issues/15237)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-28 20:49:50 UTC.

- [ ] [#15229 — SDL\_UploadToGPUTexture documentation misleading, causing performance issues in DX12](https://github.com/libsdl-org/SDL/issues/15229)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 18:57:40 UTC.

- [ ] [#15125 — possible memory leak for \`SDL\_CreateWindowAndRenderer\`](https://github.com/libsdl-org/SDL/issues/15125)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 22:26:39 UTC.

- [ ] [#15118 — Emscripten: how to restart a SDL demo without refresh the page after navigating forward/back?](https://github.com/libsdl-org/SDL/issues/15118)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 18:41:14 UTC.

- [ ] [#15108 — Suspending an application on Xbox platforms is impossible](https://github.com/libsdl-org/SDL/issues/15108)
  - **Motiv:** Integrare lifecycle Xbox: responsabilitatea aplicației versus SDL trebuie clarificată înainte de a numi comportamentul bug de bibliotecă.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-30 15:53:57 UTC.
  - **Context:** Maintainerul explică nevoia intervenției aplicației la suspend și cere un reproducător minimal. [Discuție](https://github.com/libsdl-org/SDL/issues/15108#issuecomment-4353990729).

- [ ] [#15105 — macOS/ANGLE: SDL\_GL\_SetSwapInterval(1) is ignored](https://github.com/libsdl-org/SDL/issues/15105)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-02-25 03:27:53 UTC.

- [ ] [#15089 — SDL\_SCALEMODE seems to have no effect on macOS](https://github.com/libsdl-org/SDL/issues/15089)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.6.0` · Actualizat: 2026-06-23 16:08:33 UTC.

- [ ] [#15086 — SDL\_getenv() shoudl be case-insensitive (at least on Windows)](https://github.com/libsdl-org/SDL/issues/15086)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-12 04:04:24 UTC.

- [ ] [#15071 — Fullscreen weirdness on macOS with camera notch (SDL\_GetWindowSafeArea / SDL\_GetDisplayUsableBounds)](https://github.com/libsdl-org/SDL/issues/15071)
  - **Motiv:** Clarificări safe area/notch rămase; componenta glScissor a fost atribuită aplicației.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-17 04:08:56 UTC.
  - **Context:** Autorul confirmă că matricea de proiecție neactualizată era propria eroare; întrebările despre notch rămân. [Discuție](https://github.com/libsdl-org/SDL/issues/15071#issuecomment-3945274489).

- [ ] [#15069 — Graphical stuttering in Linux with SDL3 GPU](https://github.com/libsdl-org/SDL/issues/15069)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 22:32:06 UTC.

- [ ] [#15064 — SDL\_CreateCursor not displaying inverted colours on Windows](https://github.com/libsdl-org/SDL/issues/15064)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 18:29:41 UTC.

- [ ] [#15061 — Android project is obsolete.](https://github.com/libsdl-org/SDL/issues/15061)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 18:25:05 UTC.

- [ ] [#15037 — \[Win32\] \`SDL\_EVENT\_WINDOW\_EXPOSED\` seems to not be sent during Moves](https://github.com/libsdl-org/SDL/issues/15037)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-02-12 16:56:34 UTC.

- [ ] [#15003 — v4l2loopback gets filtered](https://github.com/libsdl-org/SDL/issues/15003)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-02-08 18:04:37 UTC.

- [ ] [#14974 — SDL\_CaptureMouse(SDL\_TRUE) failing to capture mouse when it leaves ?positive window area.](https://github.com/libsdl-org/SDL/issues/14974)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-23 21:51:14 UTC.

- [ ] [#14968 — D3D12 GPU renderer is locked to refresh rate](https://github.com/libsdl-org/SDL/issues/14968)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 19:04:42 UTC.

- [ ] [#14963 — Clarify ownership and lifetime semantics for opaque handles in documentation](https://github.com/libsdl-org/SDL/issues/14963)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 22:36:09 UTC.

- [ ] [#14945 — Non-fatal exceptions are thrown during GPU Renderer creation](https://github.com/libsdl-org/SDL/issues/14945)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 23:24:05 UTC.

- [ ] [#14905 — SDL KMSDRM output doesn't take into account drm panel orientation](https://github.com/libsdl-org/SDL/issues/14905)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-25 16:24:47 UTC.

- [ ] [#14904 — SDL\_SimpleMessageBox fails with \`posix\_spawn() failed: No such file or directory\` on X11](https://github.com/libsdl-org/SDL/issues/14904)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-08-28 09:17:20 UTC.

- [ ] [#14876 — Inconsistent \`SDL\_ShowOpenFileDialog\` parameter \`default\_location\` behavior across platforms](https://github.com/libsdl-org/SDL/issues/14876)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 22:39:45 UTC.

- [ ] [#14835 — \[PS2\] Audio Stutter](https://github.com/libsdl-org/SDL/issues/14835)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 22:40:19 UTC.

- [ ] [#14798 — Creating indexed textures with formats less than 8 bits gets caught by a param check.](https://github.com/libsdl-org/SDL/issues/14798)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-02-01 00:05:59 UTC.

- [ ] [#14791 — SDL GPU adds 1 frame of latency](https://github.com/libsdl-org/SDL/issues/14791)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-25 16:21:14 UTC.

- [ ] [#14788 — SDL3:Pen:Linux: RMB and MMB are confused](https://github.com/libsdl-org/SDL/issues/14788)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-05-11 16:27:03 UTC.

- [ ] [#14785 — SDL\_ASSERT\_LEVEL set incorrectly with gcc -Og flag set](https://github.com/libsdl-org/SDL/issues/14785)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-12 19:31:25 UTC.

- [ ] [#14777 — when changing from full screen to windowed, on dual monitor system it blacks both screens out](https://github.com/libsdl-org/SDL/issues/14777)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-23 21:09:29 UTC.

- [ ] [#14775 — Noticeable screen tearing in SDL 3.4.0 compared to SDL 3.2.22 (without vsync)](https://github.com/libsdl-org/SDL/issues/14775)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-16 19:16:54 UTC.

- [ ] [#14766 — SDL3:Pen:Wayland: SDL does not produce axis (at least pressure) events sometimes](https://github.com/libsdl-org/SDL/issues/14766)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-29 20:24:11 UTC.

- [ ] [#14763 — Live resize glitches for "vulkan" driver, and even more for "gpu"](https://github.com/libsdl-org/SDL/issues/14763)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-17 15:10:07 UTC.

- [ ] [#14749 — Building SDL3 with buildroot for raspberry pi \<4 targets fails on the linking stage](https://github.com/libsdl-org/SDL/issues/14749)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-23 21:12:32 UTC.

- [ ] [#14738 — SDL\_GetClipboardMimeTypes() doesn't work on macOS](https://github.com/libsdl-org/SDL/issues/14738)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-23 21:13:12 UTC.

- [ ] [#14725 — Minimized windows continue to get mouse events from "ghost area"](https://github.com/libsdl-org/SDL/issues/14725)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-31 15:48:33 UTC.

- [ ] [#14713 — Reconsider xpadneo profile switching implementation](https://github.com/libsdl-org/SDL/issues/14713)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-29 18:02:59 UTC.

- [ ] [#14674 — Detecting refresh rate changes](https://github.com/libsdl-org/SDL/issues/14674)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-23 02:03:32 UTC.

- [ ] [#14671 — Correct usage of the -pthread flag.](https://github.com/libsdl-org/SDL/issues/14671)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-22 16:54:13 UTC.

- [ ] [#14654 — SDL\_FRect for renderer clip rectangle](https://github.com/libsdl-org/SDL/issues/14654)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-17 04:09:13 UTC.

- [ ] [#14612 — Implement storage copy and rename fallback implementations](https://github.com/libsdl-org/SDL/issues/14612)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 17:52:24 UTC.

- [ ] [#14611 — Standardize and document storage paths](https://github.com/libsdl-org/SDL/issues/14611)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-17 14:21:02 UTC.

- [ ] [#14598 — SDL doesn't receive SDL\_EVENT\_MOUSE\_BUTTON\_UP when SDL\_EVENT\_MOUSE\_BUTTON\_DOWN was done before SDLWindow created](https://github.com/libsdl-org/SDL/issues/14598)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 17:58:26 UTC.

- [ ] [#14574 — Emscripten: queue fullscreen toggles](https://github.com/libsdl-org/SDL/issues/14574)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2025-12-03 15:08:36 UTC.

- [ ] [#14558 — audio: Remove the minimum device spec.](https://github.com/libsdl-org/SDL/issues/14558)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-11 19:19:58 UTC.

- [ ] [#14512 — GDK main function may leak resources](https://github.com/libsdl-org/SDL/issues/14512)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-11-23 19:16:03 UTC.

- [ ] [#14462 — Android multi audio device issues](https://github.com/libsdl-org/SDL/issues/14462)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-11-14 04:46:55 UTC.

- [ ] [#14456 — Bad Frame Lag on Metal SDL3 GPU](https://github.com/libsdl-org/SDL/issues/14456)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-09-04 20:54:08 UTC.

- [ ] [#14451 — PS4 controller is detected as joystick but not as gamepad](https://github.com/libsdl-org/SDL/issues/14451)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `notourbug` · Milestone: `3.x` · Actualizat: 2025-12-19 18:44:26 UTC.

- [ ] [#14413 — EGL\_BAD\_ACCESS when calling SDL\_GL\_MakeCurrent() from worker thread on Wayland (Mesa 25+) — request: surfaceless make-current API](https://github.com/libsdl-org/SDL/issues/14413)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-29 16:01:49 UTC.

- [ ] [#14361 — Touchpad works fine in X11 but has touchscreen behaviour in KMSDRM](https://github.com/libsdl-org/SDL/issues/14361)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-07-02 03:56:00 UTC.

- [ ] [#14349 — Allow confining a hardare cursor to the window rect automatically](https://github.com/libsdl-org/SDL/issues/14349)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2025-10-31 17:20:40 UTC.

- [ ] [#14184 — Incorrect labeling on BR-ABNT keyboard layout](https://github.com/libsdl-org/SDL/issues/14184)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2025-11-02 15:27:22 UTC.

- [ ] [#14158 — Specify the adapter used when creating a GPU device](https://github.com/libsdl-org/SDL/issues/14158)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-09-07 01:25:19 UTC.

- [ ] [#14153 — \[Windows\] Hidden cursor appears after tabbing out and in with Windows key.](https://github.com/libsdl-org/SDL/issues/14153)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-14 05:36:48 UTC.

- [ ] [#14077 — GPU renderer: implement external texture support](https://github.com/libsdl-org/SDL/issues/14077)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-25 16:23:51 UTC.

- [ ] [#14044 — \[Linux\] Switch charging grip mappings broken when using hid-nintendo evdev](https://github.com/libsdl-org/SDL/issues/14044)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-13 17:38:51 UTC.

- [ ] [#13992 — macOS CI occasionally fails with timeout](https://github.com/libsdl-org/SDL/issues/13992)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-27 00:08:09 UTC.

- [ ] [#13965 — WASAPI WINE static sounds](https://github.com/libsdl-org/SDL/issues/13965)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-08 17:49:05 UTC.

- [ ] [#13871 — GPU: same-texture read/write bindings at different mip levels and read-only depth+sampler usage?](https://github.com/libsdl-org/SDL/issues/13871)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-09 02:52:16 UTC.

- [ ] [#13785 — SDL3 Clipboard support in Emscripten](https://github.com/libsdl-org/SDL/issues/13785)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-28 16:08:42 UTC.

- [ ] [#13780 — Chromebook switch controller doesn't register](https://github.com/libsdl-org/SDL/issues/13780)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 12:44:45 UTC.

- [ ] [#13769 — Audio stops working if execution is suspended (.NET process)](https://github.com/libsdl-org/SDL/issues/13769)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2025-10-08 18:11:56 UTC.

- [ ] [#13751 — Add/Compare new audio resampler to src.infinitewave.ca tests](https://github.com/libsdl-org/SDL/issues/13751)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-01 08:30:16 UTC.

- [ ] [#13745 — (macos) Assertion failed dialog stays always on top when breaking into debugger](https://github.com/libsdl-org/SDL/issues/13745)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 00:40:55 UTC.

- [ ] [#13730 — \[Examples\] Stuttering when moving window on Windows](https://github.com/libsdl-org/SDL/issues/13730)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-11 14:02:39 UTC.

- [ ] [#13718 — SDL Window not showing on Hyprland](https://github.com/libsdl-org/SDL/issues/13718)
  - **Motiv:** Discuția recentă sugerează problemă în stack-ul Vulkan/driver/OS și ameliorare după actualizarea sistemului.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-31 07:12:43 UTC.
  - **Context:** Un participant nu mai reproduce după actualizarea pachetelor; cauza exactă rămâne necunoscută. [Discuție](https://github.com/libsdl-org/SDL/issues/13718#issuecomment-3222657197).

- [ ] [#13650 — Fullscreen mode in macOS (SDL3)](https://github.com/libsdl-org/SDL/issues/13650)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-08 06:22:38 UTC.

- [ ] [#13486 — \[SDL3 + ffmpeg\] Can't read a h264 file using VAAPI with a Nvidia GPU.](https://github.com/libsdl-org/SDL/issues/13486)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-20 05:19:23 UTC.

- [ ] [#13474 — FPS limit not works in Windows](https://github.com/libsdl-org/SDL/issues/13474)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 00:34:46 UTC.

- [ ] [#13471 — dwmapi error](https://github.com/libsdl-org/SDL/issues/13471)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-07-31 14:20:51 UTC.

- [ ] [#13461 — HID batteries show up as joysticks on custom controller](https://github.com/libsdl-org/SDL/issues/13461)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 13:35:11 UTC.

- [ ] [#13443 — Infinite vibration on some controllers](https://github.com/libsdl-org/SDL/issues/13443)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-07-28 15:48:53 UTC.

- [ ] [#13358 — SDL\_DISABLE\_ALLOCA should be set on MinGW, but appears to be enabled](https://github.com/libsdl-org/SDL/issues/13358)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 00:22:35 UTC.

- [ ] [#13329 — Issue with subpixel rendering](https://github.com/libsdl-org/SDL/issues/13329)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-17 00:29:37 UTC.

- [ ] [#13328 — \[SDL GPU\] Vulkan backend by default interprets storage buffers as readonly but D3D12 interprets as readwrite](https://github.com/libsdl-org/SDL/issues/13328)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 13:35:43 UTC.

- [ ] [#13316 — Direct3D9 renderer doesn't work with an external window](https://github.com/libsdl-org/SDL/issues/13316)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-07-11 20:38:10 UTC.

- [ ] [#13289 — SDL\_migration.cocci does not write any patch output](https://github.com/libsdl-org/SDL/issues/13289)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-29 14:28:09 UTC.

- [ ] [#13249 — G27 Shifter Adapter gets mapped as gamepad](https://github.com/libsdl-org/SDL/issues/13249)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-13 13:56:14 UTC.

- [ ] [#13228 — Simple render to texture messes up alpha](https://github.com/libsdl-org/SDL/issues/13228)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 14:50:29 UTC.

- [ ] [#13216 — Android: Relative mouse mode doesn't work on BlueStacks emulator](https://github.com/libsdl-org/SDL/issues/13216)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 14:51:56 UTC.

- [ ] [#13195 — When SDL relative mouse mode is on and a break point is hit while debugging.](https://github.com/libsdl-org/SDL/issues/13195)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 15:03:40 UTC.

- [ ] [#13144 — SDL 3: HORIPAD connection issues](https://github.com/libsdl-org/SDL/issues/13144)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-05-29 16:01:16 UTC.

- [ ] [#13142 — evdev open is delayed](https://github.com/libsdl-org/SDL/issues/13142)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-05-31 06:07:57 UTC.

- [ ] [#13072 — OpenGL MSAA Not Working with SDL\_Renderer](https://github.com/libsdl-org/SDL/issues/13072)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-27 20:49:50 UTC.

- [ ] [#13021 — SDL\_gameinput.cpp has line #include \<game\_input.h\>, but game\_input does not exist](https://github.com/libsdl-org/SDL/issues/13021)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-18 20:37:05 UTC.

- [ ] [#13019 — \[SDL3, CAMERA SUBSYSTEM\] V4L2 backend refuses to recognize certain webcams.](https://github.com/libsdl-org/SDL/issues/13019)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-07-29 10:34:49 UTC.

- [ ] [#12932 — SDL\_HideCursor does not hide cursor before moving the mouse if the window is maximized](https://github.com/libsdl-org/SDL/issues/12932)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `notourbug` · Milestone: `3.x` · Actualizat: 2025-05-02 15:43:02 UTC.

- [ ] [#12921 — macOS 15.4.1 Crash on SDL\_Quit when using Multi - Threading](https://github.com/libsdl-org/SDL/issues/12921)
  - **Motiv:** Crash raportat pe versiuni macOS mai vechi; retestarea compatibilității are prioritate față de presupunerea unui defect SDL curent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-31 16:12:03 UTC.
  - **Context:** Maintainerul nu reproduce pe macOS mai nou și sugerează că OS-ul a remediat cazul. [Discuție](https://github.com/libsdl-org/SDL/issues/12921#issuecomment-3702452972).

- [ ] [#12911 — \[SDL3\] SDL\_WINDOW\_TRANSPARENT gives black background on LxQt and dwm](https://github.com/libsdl-org/SDL/issues/12911)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-30 16:46:05 UTC.

- [ ] [#12904 — \[SDL3\] SDL\_SetWindowFullscreenMode() implementation seems inconsistent and unreliable](https://github.com/libsdl-org/SDL/issues/12904)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-05-22 11:22:00 UTC.

- [ ] [#12886 — SDL2 on macOS detects joysticks only with SDL2\_INIT\_VIDEO](https://github.com/libsdl-org/SDL/issues/12886)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-25 16:54:12 UTC.

- [ ] [#12875 — macOS: întârziere la inițierea dragului între ecranul MacBook Pro de 120 Hz și monitorul extern de 60 Hz](https://github.com/libsdl-org/SDL/issues/12875)
  - Rezumat editorial; titlul integral este disponibil în issue.
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-02-24 17:05:14 UTC.

- [ ] [#12856 — SDL3: Lag on first key press (MacOS)](https://github.com/libsdl-org/SDL/issues/12856)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-19 15:26:26 UTC.

- [ ] [#12825 — \[SDL3\] \[GPU\] Unable to use MTLVertexStepFunctionConstant for metal backend](https://github.com/libsdl-org/SDL/issues/12825)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-24 20:25:53 UTC.

- [ ] [#12791 — SDL3: OpenGL Borderless Window Becomes Exclusive Fullscreen on \`SDL\_GL\_SwapWindow\` (Windows 11)](https://github.com/libsdl-org/SDL/issues/12791)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-08-24 01:32:18 UTC.

- [ ] [#12787 — SDL3 OpenGL shared context with no stencil bits prevents stencil usage in window OpenGL context with stencil bits -- intended?](https://github.com/libsdl-org/SDL/issues/12787)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2025-10-08 17:26:02 UTC.

- [ ] [#12770 — \`SDL\_GetGlobalMouseState\` and \`SDL\_GetWindowPosition\` inconsistency still present on Emscripten](https://github.com/libsdl-org/SDL/issues/12770)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2025-11-15 01:56:10 UTC.

- [ ] [#12732 — Valgrind reports memory leak in SinkInfoCallback](https://github.com/libsdl-org/SDL/issues/12732)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-27 20:54:02 UTC.

- [ ] [#12697 — Windows clipboard "text/html" data not available.](https://github.com/libsdl-org/SDL/issues/12697)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-23 22:59:44 UTC.

- [ ] [#12685 — \`SDL\_TouchFingerEvent\` events not generated on a Steam Deck under Proton](https://github.com/libsdl-org/SDL/issues/12685)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-28 21:56:33 UTC.

- [ ] [#12678 — Hidden \`SDL\_Window\*\` used as shared GL context fails on Emscripten](https://github.com/libsdl-org/SDL/issues/12678)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 16:14:07 UTC.

- [ ] [#12671 — X11: SDL\_SetWindowMouseRect not working reliably](https://github.com/libsdl-org/SDL/issues/12671)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-26 16:28:10 UTC.

- [ ] [#12647 — WASAPI audio briefly cutting out](https://github.com/libsdl-org/SDL/issues/12647)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-05-09 01:26:11 UTC.

- [ ] [#12609 — SDL3: probleme agregate de prezentare, inițializare Vulkan și ferestre](https://github.com/libsdl-org/SDL/issues/12609)
  - Rezumat editorial; titlul integral este disponibil în issue.
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-14 19:34:03 UTC.

- [ ] [#12601 — PySDL3 doesn't draw a sprite](https://github.com/libsdl-org/SDL/issues/12601)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 18:57:03 UTC.

- [ ] [#12564 — SDL3 Windows: Child window should work with relative mouse mode](https://github.com/libsdl-org/SDL/issues/12564)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-12 23:00:17 UTC.

- [ ] [#12528 — \[SDL3.2.8\] \[Win32\] Moving or resizing window is stuttery](https://github.com/libsdl-org/SDL/issues/12528)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-21 04:09:33 UTC.

- [ ] [#12517 — SDL2: On windows releasing right button on title bar cause open context menu](https://github.com/libsdl-org/SDL/issues/12517)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-24 18:06:23 UTC.

- [ ] [#12511 — SDL\_DINPUT\_HapticUpdateEffect sends unnecessary flags to IDirectInputEffect\_SetParameters, which harms FFB quality in certain devices/usecases](https://github.com/libsdl-org/SDL/issues/12511)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-03 00:31:25 UTC.

- [ ] [#12506 — GPU renderer double-copies locked textures](https://github.com/libsdl-org/SDL/issues/12506)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-10 16:14:30 UTC.

- [ ] [#12473 — Add support for mouse warp using libei](https://github.com/libsdl-org/SDL/issues/12473)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-05 20:21:03 UTC.

- [ ] [#12467 — Text drag and drop in SDL 3 under Ubuntu 24.04 LTS in VirtualBox not working](https://github.com/libsdl-org/SDL/issues/12467)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 14:55:37 UTC.

- [ ] [#12451 — Mode changes not working in XWayland](https://github.com/libsdl-org/SDL/issues/12451)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `notourbug` · Milestone: `3.x` · Actualizat: 2025-08-26 23:47:20 UTC.

- [ ] [#12418 — "kmsdrm" driver not working on Raspberry Pi](https://github.com/libsdl-org/SDL/issues/12418)
  - **Motiv:** Mai întâi verificați cerințele de event pumping/redraw ale backendului și exemplul aplicației.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-16 19:34:04 UTC.
  - **Context:** Discuția cere procesarea evenimentelor chiar dacă aplicația nu consumă input; nu confirmă un fix în backend. [Discuție](https://github.com/libsdl-org/SDL/issues/12418#issuecomment-3662069532).

- [ ] [#12377 — Cross compile for rasperry pi...](https://github.com/libsdl-org/SDL/issues/12377)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 14:57:48 UTC.

- [ ] [#12348 — \[SDL 3.2.4\] Resizing the window makes it move](https://github.com/libsdl-org/SDL/issues/12348)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `notourbug` · Milestone: `3.x` · Actualizat: 2025-02-21 16:48:02 UTC.

- [ ] [#12333 — SDL3: SDL\_RenderPresent slows down over time to a peak point and remains](https://github.com/libsdl-org/SDL/issues/12333)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-04 19:39:47 UTC.

- [ ] [#12302 — SDL\_AppIterate behaviour on macOS](https://github.com/libsdl-org/SDL/issues/12302)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:06:31 UTC.

- [ ] [#12299 — SDL3 slight window freeze on resize Windows 11](https://github.com/libsdl-org/SDL/issues/12299)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-13 10:51:02 UTC.

- [ ] [#12294 — README-cmake.md instructions on library copying are incorrect](https://github.com/libsdl-org/SDL/issues/12294)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-02-14 18:14:20 UTC.

- [ ] [#12280 — sdl3 build fails to find EGL/egl.h due to incorrect include path](https://github.com/libsdl-org/SDL/issues/12280)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-02-12 19:04:47 UTC.

- [ ] [#12272 — Ubuntu Touch/Lomiri support](https://github.com/libsdl-org/SDL/issues/12272)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:06:45 UTC.

- [ ] [#12269 — \[Pipewire\] Sampling Rate Issues](https://github.com/libsdl-org/SDL/issues/12269)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-21 17:31:41 UTC.

- [ ] [#12249 — Issues with L/R trigger with generic HID gamepad and Windows DInput](https://github.com/libsdl-org/SDL/issues/12249)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-02-11 02:01:26 UTC.

- [ ] [#12246 — SDL\_CreateTray doesn't seem to support (NULL, NULL)  or SDL\_Surface when being called in Linux.](https://github.com/libsdl-org/SDL/issues/12246)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:07:14 UTC.

- [ ] [#12230 — SDL\_SetCursor doesn't work very well on Mac external monitors](https://github.com/libsdl-org/SDL/issues/12230)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2025-12-02 15:40:17 UTC.

- [ ] [#12213 — Migrating displays on kmsdrm](https://github.com/libsdl-org/SDL/issues/12213)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2025-08-26 22:39:18 UTC.

- [ ] [#12201 — Clarify in documentation how SDL\_StorageReady() should be used](https://github.com/libsdl-org/SDL/issues/12201)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-19 01:01:30 UTC.

- [ ] [#12189 — Optimal OpenGL pixel formats for Mac OS X?](https://github.com/libsdl-org/SDL/issues/12189)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:11:46 UTC.

- [ ] [#12088 — \[MacOS\] Vsync has issues on MacOS](https://github.com/libsdl-org/SDL/issues/12088)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2025-11-14 04:34:55 UTC.

- [ ] [#12082 — SDL 3.2 Xbox Gamepad Axes incorrect on Windows](https://github.com/libsdl-org/SDL/issues/12082)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2025-02-25 16:34:03 UTC.

- [ ] [#12081 — \[MacOS\] Resize flicker](https://github.com/libsdl-org/SDL/issues/12081)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 17:51:37 UTC.

- [ ] [#12070 — On Windows, consider also the information from pixel format descriptor in \`SDL\_GL\_GetAttribute()\` queries](https://github.com/libsdl-org/SDL/issues/12070)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-06 15:42:52 UTC.

- [ ] [#12049 — GPU: Add resource usage flag validation](https://github.com/libsdl-org/SDL/issues/12049)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-23 21:16:35 UTC.

- [ ] [#12040 — 3.1.10 VisualStudio build doesn't copy all resource files for tests](https://github.com/libsdl-org/SDL/issues/12040)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-11-24 23:30:59 UTC.

- [ ] [#12038 — GitHub runner \`macos-14-arm64\` fails: 'EGL/egl.h' file not found](https://github.com/libsdl-org/SDL/issues/12038)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:26:29 UTC.

- [ ] [#11989 — No TaskbarCreated Listener in Tray on Windows Platform](https://github.com/libsdl-org/SDL/issues/11989)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-16 07:26:59 UTC.

- [ ] [#11930 — SDL3: Constant crackling sound in \`02-simple-playback-callback\` on Debian with Chromium and Firefox](https://github.com/libsdl-org/SDL/issues/11930)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-20 18:26:19 UTC.

- [ ] [#11867 — xp/vista relative mouse system scale](https://github.com/libsdl-org/SDL/issues/11867)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-21 00:49:02 UTC.

- [ ] [#11849 — duplicate entries for 8bitdo ultimate bluetooth controller on windows](https://github.com/libsdl-org/SDL/issues/11849)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-07-27 14:29:14 UTC.

- [ ] [#11820 — GPU: Destroying swapchains (on nvidia vulkan?) corrupts driver state and causes random crashes](https://github.com/libsdl-org/SDL/issues/11820)
  - **Motiv:** Retestare cu driver nou: cauza este atribuită NVIDIA, nu un fix SDL confirmat ca restant.
  - **GitHub:** OPEN · Etichete: `notourbug` · Milestone: `3.x` · Actualizat: 2025-03-18 21:16:24 UTC.
  - **Context:** Autorul spune că NVIDIA a identificat cauza și validează o remediere; păstrat deschis, fără a declara rezolvarea completă. [Discuție](https://github.com/libsdl-org/SDL/issues/11820#issuecomment-2734749536).

- [ ] [#11812 — Test SDL\_GPU on ci](https://github.com/libsdl-org/SDL/issues/11812)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:29:56 UTC.

- [ ] [#11807 — Child windows can steal focus with mouse input while in relative mode](https://github.com/libsdl-org/SDL/issues/11807)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-16 03:28:36 UTC.

- [ ] [#11792 — Repeated compilation](https://github.com/libsdl-org/SDL/issues/11792)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-24 18:08:13 UTC.

- [ ] [#11782 — Requesting unknown permission on Android fails, should default to indicate permission being granted](https://github.com/libsdl-org/SDL/issues/11782)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-31 11:52:58 UTC.

- [ ] [#11759 — Errors when building SDL3.dll with -DSDL\_LIBC=OFF](https://github.com/libsdl-org/SDL/issues/11759)
  - **Motiv:** Conform discuției, build-ul DLL a fost reparat; rămâne adăugarea unui job CI fără libc.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-02-02 00:03:43 UTC.
  - **Context:** Issue-ul este păstrat deschis pentru acoperire CI, nu ca dovadă a unui build DLL încă defect. [Discuție](https://github.com/libsdl-org/SDL/issues/11759#issuecomment-2605734000).

- [ ] [#11724 — \[SDL3\] 3.1.7 IOS Abnormal audio playback](https://github.com/libsdl-org/SDL/issues/11724)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-20 18:24:57 UTC.

- [ ] [#11652 — Significant lag to update window after resize event](https://github.com/libsdl-org/SDL/issues/11652)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-07-14 18:03:50 UTC.

- [ ] [#11631 — ERROR: Could not queue pageflip: -16](https://github.com/libsdl-org/SDL/issues/11631)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:36:47 UTC.

- [ ] [#11618 — Linux - OpenGL content jitter on window vertical resize](https://github.com/libsdl-org/SDL/issues/11618)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-30 03:07:28 UTC.

- [ ] [#11617 — Keymod from held modifier key is lost when setting/clearing full-screen.](https://github.com/libsdl-org/SDL/issues/11617)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-14 20:00:16 UTC.

- [ ] [#11582 — Multithreaded emscripten is currently not part of the test matrix.](https://github.com/libsdl-org/SDL/issues/11582)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 16:58:00 UTC.

- [ ] [#11471 — SDL3 joystick axis values sometimes not scaled correctly](https://github.com/libsdl-org/SDL/issues/11471)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-03 01:03:09 UTC.

- [ ] [#11446 — SDL3 Xcode project: SDL3.xcframework build fails if an unwanted platform is not installed.](https://github.com/libsdl-org/SDL/issues/11446)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-08 22:05:08 UTC.

- [ ] [#11443 — \[SDL3\] Artifacts when rendering texture ](https://github.com/libsdl-org/SDL/issues/11443)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:48:23 UTC.

- [ ] [#11438 — SDL3.1.6 Windows default renderer very choppy](https://github.com/libsdl-org/SDL/issues/11438)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-06-23 00:10:04 UTC.

- [ ] [#11336 — Windows: handle rawkeyboard on the main thread, and use rawkeyboard by default](https://github.com/libsdl-org/SDL/issues/11336)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:52:23 UTC.

- [ ] [#11329 — OpenVR has a link dependency on libEGL.so.1](https://github.com/libsdl-org/SDL/issues/11329)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-28 20:23:14 UTC.

- [ ] [#11325 — SDL\_clipboard thread safety documentation might be too restrictive](https://github.com/libsdl-org/SDL/issues/11325)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 19:38:41 UTC.

- [ ] [#11324 — Android opengles2: First \`SDL\_RenderPresent()\` broken after resize](https://github.com/libsdl-org/SDL/issues/11324)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-18 14:28:32 UTC.

- [ ] [#11319 — SDL\_PollEvent gives a sentinel event and returns true](https://github.com/libsdl-org/SDL/issues/11319)
  - **Motiv:** Posibilă incompatibilitate ABI/FFI bool-versus-int; verificați semnăturile înainte de a atribui loop-ul SDL.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-02-25 16:35:51 UTC.
  - **Context:** Un participant descrie aceeași manifestare la folosirea semnăturii SDL2 pentru SDL3; aceasta este o ipoteză pentru raportul inițial. [Discuție](https://github.com/libsdl-org/SDL/issues/11319#issuecomment-3960293808).

- [ ] [#11293 — GPU: Threaded vkQueuePresentKHR](https://github.com/libsdl-org/SDL/issues/11293)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-26 22:42:35 UTC.

- [ ] [#11246 — Relative mouse mode drag does not report mouse button state.](https://github.com/libsdl-org/SDL/issues/11246)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-14 20:46:09 UTC.

- [ ] [#11239 — SDL\_SyncWindow can time out under normal conditions with a slow computer, with X11 backend](https://github.com/libsdl-org/SDL/issues/11239)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-26 23:30:19 UTC.

- [ ] [#11102 — Rendering buffer after resizing uses old window size on "gpu" and "software" render drivers on Wayland and X11](https://github.com/libsdl-org/SDL/issues/11102)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 19:27:07 UTC.

- [ ] [#11091 — SDL3: Rename library includes on macos or change folder structure -\> by default includes have wrong naming](https://github.com/libsdl-org/SDL/issues/11091)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-02-19 19:38:04 UTC.

- [ ] [#10934 — macOS modifiers become sticky when released simultaneously](https://github.com/libsdl-org/SDL/issues/10934)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2024-12-29 16:01:11 UTC.

- [ ] [#10905 — macOS: spurious key events](https://github.com/libsdl-org/SDL/issues/10905)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 18:42:06 UTC.

- [ ] [#10751 — Guitar button not working (Rock Band)](https://github.com/libsdl-org/SDL/issues/10751)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-06 12:13:46 UTC.

- [ ] [#10702 — GPU: Consider timeout parameter on AcquireSwapchainTexture/Wait/WaitForFences](https://github.com/libsdl-org/SDL/issues/10702)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `enhancement` · Milestone: `3.x` · Actualizat: 2024-10-06 20:24:10 UTC.

- [ ] [#10610 — Sanity check for CMake Configures](https://github.com/libsdl-org/SDL/issues/10610)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 18:29:48 UTC.

- [ ] [#10572 — testffmpeg poor performance](https://github.com/libsdl-org/SDL/issues/10572)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 19:25:40 UTC.

- [ ] [#10539 — \[macos\] HIDAPI device disconnected while opening](https://github.com/libsdl-org/SDL/issues/10539)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2025-03-10 20:26:12 UTC.

- [ ] [#10506 — WASAPI can't find requested audio endpoint: Element not found.](https://github.com/libsdl-org/SDL/issues/10506)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 23:22:09 UTC.

- [ ] [#10470 — testffmpeg default (gles EGL) fails](https://github.com/libsdl-org/SDL/issues/10470)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 21:33:07 UTC.

- [ ] [#10466 — Many tests lack controller support](https://github.com/libsdl-org/SDL/issues/10466)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 20:33:56 UTC.

- [ ] [#10451 — SDL\_NumJoysticks() is returning 2 joysticks when only 1 is plugged in](https://github.com/libsdl-org/SDL/issues/10451)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2024-12-21 16:21:38 UTC.

- [ ] [#10432 — Failed to open audio recording device \[name\]. SDL Error: CoreAudio error (AudioQueueStart): -66681 \[MacOS\]](https://github.com/libsdl-org/SDL/issues/10432)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `Apple` · Milestone: `3.x` · Actualizat: 2025-01-04 17:46:18 UTC.

- [ ] [#10412 — Long SDL\_Init() time when Haptics enabled](https://github.com/libsdl-org/SDL/issues/10412)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-30 10:47:56 UTC.

- [ ] [#10344 — PSP renderer should create streaming textures in VRAM](https://github.com/libsdl-org/SDL/issues/10344)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-08-22 18:35:45 UTC.

- [ ] [#10326 — Why does SDL try to make reference to emscripten webgl if I've disabled all renderers?](https://github.com/libsdl-org/SDL/issues/10326)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 18:21:18 UTC.

- [ ] [#9989 — \[Camera\]: SDL\_GetCameraPermissionState returns 0 if pipewire backend is being used](https://github.com/libsdl-org/SDL/issues/9989)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-04 21:15:39 UTC.

- [ ] [#9880 — Emscripten: TypeError when switching renderer from opengles2 to software](https://github.com/libsdl-org/SDL/issues/9880)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 18:58:11 UTC.

- [ ] [#9776 — Camera: pipewire-camera back-end detects no camera](https://github.com/libsdl-org/SDL/issues/9776)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-04 21:14:41 UTC.

- [ ] [#9637 — \[Question\] Behaviour of SDL\_Quit when subsystem objects still exist](https://github.com/libsdl-org/SDL/issues/9637)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:16:10 UTC.

- [ ] [#9635 — COREAUDIO\_OpenDevice on iOS ignores sample rate](https://github.com/libsdl-org/SDL/issues/9635)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-26 22:14:36 UTC.

- [ ] [#9457 — Controller not working SDL2 Manjaro Arm64](https://github.com/libsdl-org/SDL/issues/9457)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2024-12-29 18:37:33 UTC.

- [ ] [#9434 — SDL\_ShowMessageBox can be maximized by the parent process](https://github.com/libsdl-org/SDL/issues/9434)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-17 04:06:35 UTC.

- [ ] [#9351 — Expose accessibility events/callbacks](https://github.com/libsdl-org/SDL/issues/9351)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-07-03 07:41:48 UTC.

- [ ] [#9330 — testautomation --filter audio\_initOpenCloseQuitAudio fails](https://github.com/libsdl-org/SDL/issues/9330)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 18:38:39 UTC.

- [ ] [#9263 — Linux v4l2 Camera troubles in X11 w/ SDL\_PIXELFORMAT\_YUY2](https://github.com/libsdl-org/SDL/issues/9263)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2025-01-18 14:36:46 UTC.

- [ ] [#9103 — Add Emscripten (downstream) tests for SDL 2 here](https://github.com/libsdl-org/SDL/issues/9103)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-06-03 00:34:05 UTC.

- [ ] [#9058 — Build issues in downstream enviornments](https://github.com/libsdl-org/SDL/issues/9058)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2024-12-04 18:24:28 UTC.

- [ ] [#9057 — When the window gets occluded in macos the app becomes unresponsive for one second](https://github.com/libsdl-org/SDL/issues/9057)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-08-17 19:27:08 UTC.

- [ ] [#8620 — \[cmake\]\[linux\]\[patch\]\[draft\] runtime filename/soname miss-detection](https://github.com/libsdl-org/SDL/issues/8620)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-03 05:14:26 UTC.

- [ ] [#8513 — Button mapped to SDL\_CONTROLLER\_BUTTON\_GUIDE does not trigger SDL\_ControllerButtonEvent correctly when tapped in quick succession](https://github.com/libsdl-org/SDL/issues/8513)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-21 16:23:03 UTC.

- [ ] [#8426 — SDL\_Vulkan\_LoadLibrary may fail in sandboxed Mac apps](https://github.com/libsdl-org/SDL/issues/8426)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2025-10-08 17:09:12 UTC.

- [ ] [#8404 — SDL\_HINT\_VIDEO\_FORCE\_EGL and SDL\_CreateWindowFrom() cannot be used together](https://github.com/libsdl-org/SDL/issues/8404)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-06 16:37:01 UTC.

- [ ] [#8365 — \[SDL2\] Visual Studio 2022 + Intel C++ Compiler troubles](https://github.com/libsdl-org/SDL/issues/8365)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-08-31 17:57:28 UTC.

- [ ] [#8335 — \[windows\] video\_getSetWindowGrab fails when switching to another app immediately](https://github.com/libsdl-org/SDL/issues/8335)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:37:55 UTC.

- [ ] [#8294 — Issue with the minimized flag](https://github.com/libsdl-org/SDL/issues/8294)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:37:34 UTC.

- [ ] [#8243 — Mac number pad usage is issuing both Numbers and Actions](https://github.com/libsdl-org/SDL/issues/8243)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-09-01 22:19:55 UTC.

- [ ] [#8191 — SDL3 multi monitor on macOS: problematic window placement after leaving fullscreen](https://github.com/libsdl-org/SDL/issues/8191)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-03-27 20:11:57 UTC.

- [ ] [#8135 — SDL\_GetCPUCount on Linux does not take CPU affinity into account](https://github.com/libsdl-org/SDL/issues/8135)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:33:58 UTC.

- [ ] [#8096 — audio thread-safety issues](https://github.com/libsdl-org/SDL/issues/8096)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-05-20 20:30:34 UTC.

- [ ] [#8009 — Force SDL to use ANGLE when OpenGL ES Hint is Used (and Statically Linking ANGLE)](https://github.com/libsdl-org/SDL/issues/8009)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-07 12:44:47 UTC.

- [ ] [#7867 — Audio mixers could use SIMD versions](https://github.com/libsdl-org/SDL/issues/7867)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 16:22:53 UTC.

- [ ] [#7823 — evemu-describe output for the devices that xpadneo supports](https://github.com/libsdl-org/SDL/issues/7823)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-06-21 14:38:06 UTC.

- [ ] [#7789 — \[macOS\] Vulkan rendering on another thread causes pink border while resizing when using VK\_PRESENT\_MODE\_FIFO\_KHR](https://github.com/libsdl-org/SDL/issues/7789)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 17:28:30 UTC.

- [ ] [#7690 — macOS trackpad SDL\_TouchFingerEvent arriving "clumped" and late at beginning of motion](https://github.com/libsdl-org/SDL/issues/7690)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:50:03 UTC.

- [ ] [#7627 — Setting content orientation independently from the actual framebuffer orientation](https://github.com/libsdl-org/SDL/issues/7627)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-07-08 16:58:45 UTC.

- [ ] [#7608 — emscripten how to prevent browser's hotkeys from taking over.](https://github.com/libsdl-org/SDL/issues/7608)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:16:05 UTC.

- [ ] [#7591 — Android: allow to re-do the sequence SDL\_init / SDL\_quit](https://github.com/libsdl-org/SDL/issues/7591)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:14:27 UTC.

- [ ] [#7545 — Unlimited VSync for multiple context + no double buffer?](https://github.com/libsdl-org/SDL/issues/7545)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:13:23 UTC.

- [ ] [#7499 — SDL should allow adjustments of NSWindow-styleMask on macOS](https://github.com/libsdl-org/SDL/issues/7499)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:11:48 UTC.

- [ ] [#7495 — Improve window move/resize performance on Windows](https://github.com/libsdl-org/SDL/issues/7495)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-03-17 21:19:05 UTC.

- [ ] [#7348 — Emscripten: support SDL\_StartTextInput and ShowScreenKeyboard ](https://github.com/libsdl-org/SDL/issues/7348)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-01-23 21:20:24 UTC.

- [ ] [#7140 — Document thread safety...](https://github.com/libsdl-org/SDL/issues/7140)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-02-20 19:45:07 UTC.

- [ ] [#7068 — Hint SDL\_HINT\_JOYSTICK\_HIDAPI\_XBOX\_ONE is useless](https://github.com/libsdl-org/SDL/issues/7068)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-01-12 14:46:00 UTC.

- [ ] [#6817 — For SDL Gamepads: How to map controller hubs like Mayflash DolphinBar?](https://github.com/libsdl-org/SDL/issues/6817)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-11-08 01:07:48 UTC.

- [ ] [#6561 — KMSDRM driver without OpenGL/ES?](https://github.com/libsdl-org/SDL/issues/6561)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-05-20 19:55:23 UTC.

- [ ] [#6525 — Does kmsdrm need a window before it can load OpenGL?](https://github.com/libsdl-org/SDL/issues/6525)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2025-10-08 17:08:50 UTC.

- [ ] [#6505 — macOS: IME Escape key is not working properly](https://github.com/libsdl-org/SDL/issues/6505)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-27 01:06:03 UTC.

- [ ] [#6482 — SDL2 2.24.2 (and older SDL2 as well) issues with RDP disconnecting?](https://github.com/libsdl-org/SDL/issues/6482)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-11-07 18:53:51 UTC.

- [ ] [#6441 — (Porting/compatibility issue) for virtual keyboards that don't send key press events for modifiers, SDL2 should insert them](https://github.com/libsdl-org/SDL/issues/6441)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-12-14 13:40:38 UTC.

- [ ] [#6307 — Enviroment variable to inhibit screensaver inhibition (and enable logging)](https://github.com/libsdl-org/SDL/issues/6307)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-11-07 17:11:28 UTC.

- [ ] [#6213 — \[Wayland\] Add support for reconnects when the compositor restarts](https://github.com/libsdl-org/SDL/issues/6213)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `enhancement` · Milestone: `3.x` · Actualizat: 2026-08-04 19:08:02 UTC.

- [ ] [#6080 — \[WINDOWS\] - SDL\_SetWindowSize doesn't work when the SDL Window is a child of  non-SDL Window](https://github.com/libsdl-org/SDL/issues/6080)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-29 13:47:29 UTC.

- [ ] [#5885 — SDL Audio 24 bit integer sample support](https://github.com/libsdl-org/SDL/issues/5885)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-11-07 15:14:54 UTC.

- [ ] [#5797 — Improving Windows OpenGL VSync in windowed mode](https://github.com/libsdl-org/SDL/issues/5797)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-07 02:42:29 UTC.

- [ ] [#5738 — SDL\_GetGlobalMouseState doesn't respect SDL\_HINT\_TOUCH\_MOUSE\_EVENTS](https://github.com/libsdl-org/SDL/issues/5738)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-27 18:34:20 UTC.

- [ ] [#5685 — Right-Alt key issue on non-english Windows systems](https://github.com/libsdl-org/SDL/issues/5685)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 16:56:05 UTC.

- [ ] [#5627 — On macOS, SDL Window "flashes" when switching between apps on Mission Control](https://github.com/libsdl-org/SDL/issues/5627)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-11-16 15:26:47 UTC.

- [ ] [#5543 — device not removed from SDL\_HIDAPI\_devices on surprise removal](https://github.com/libsdl-org/SDL/issues/5543)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-10-25 21:12:47 UTC.

- [ ] [#5260 — Allow customizing canvas on Emscripten](https://github.com/libsdl-org/SDL/issues/5260)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-10-25 21:37:59 UTC.

- [ ] [#5219 — android Keyboard can't really close](https://github.com/libsdl-org/SDL/issues/5219)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `waiting` · Milestone: `3.x` · Actualizat: 2023-11-07 07:09:29 UTC.

- [ ] [#5210 — \[Windows\] use EnumAdapterByGpuPreference to find the right gpu ](https://github.com/libsdl-org/SDL/issues/5210)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `early in milestone` · Milestone: `3.x` · Actualizat: 2022-10-25 21:07:28 UTC.

- [ ] [#5116 — Wiimote analog joystick detected as hat instead of axis](https://github.com/libsdl-org/SDL/issues/5116)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-11-21 17:58:57 UTC.

- [ ] [#5066 — Natural scrolling in Gnome...](https://github.com/libsdl-org/SDL/issues/5066)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-10-25 21:08:24 UTC.

- [ ] [#4679 — Audio skipping in Emscripten](https://github.com/libsdl-org/SDL/issues/4679)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-18 05:23:19 UTC.

- [ ] [#4484 — ARM assembly to address performance of blit and fill routines](https://github.com/libsdl-org/SDL/issues/4484)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-07-25 21:15:34 UTC.

- [ ] [#4177 — False alarm from SDL\_CreateWindow when using Windows with ANGLE.](https://github.com/libsdl-org/SDL/issues/4177)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: `early in milestone` · Milestone: `3.x` · Actualizat: 2022-11-05 17:35:41 UTC.

- [ ] [#3803 — SDL\_WINDOW\_FULLSCREEN\_DESKTOP doesn't take xrandr desktop scaling into account on Linux](https://github.com/libsdl-org/SDL/issues/3803)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 17:13:17 UTC.

- [ ] [#3759 — HighDPI: Assert messagebox is not readable](https://github.com/libsdl-org/SDL/issues/3759)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-05-20 00:07:20 UTC.

- [ ] [#3620 — Warnings "Unbalanced calls ... to SDL\_uikitviewcontroller"](https://github.com/libsdl-org/SDL/issues/3620)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-11-06 16:32:18 UTC.

- [ ] [#3192 — Setting window to fullscreen on a monitor (SDL\_WINDOW\_FULLSCREEN) other than the primary will inevitably move the window back to primary monitor.](https://github.com/libsdl-org/SDL/issues/3192)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 17:09:20 UTC.

- [ ] [#2974 — a \_lot\_ of strict aliasing warnings](https://github.com/libsdl-org/SDL/issues/2974)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-11-07 01:14:17 UTC.

- [ ] [#2429 — Mac: normal-window and fullscreen-window each on its own screen does not work](https://github.com/libsdl-org/SDL/issues/2429)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:49:39 UTC.

- [ ] [#1677 — Support HW scaler in Android](https://github.com/libsdl-org/SDL/issues/1677)
  - **Motiv:** Compatibilitate, funcționalitate incompletă, performanță sau impact încă neclar; triere normală, fără defect critic confirmat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 16:21:13 UTC.

## LOW

- [ ] [#16258 — This is a question regarding the unique identification of the equipment.](https://github.com/libsdl-org/SDL/issues/16258)
  - **Motiv:** Cerere de API/capabilitate nouă, reorganizare sau convenție; nu este demonstrată o urgență în funcționalitatea existentă.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-09-07 17:16:25 UTC.

- [ ] [#16255 — Set app\_id of zenity dialogs if zenity is \>= 4.4](https://github.com/libsdl-org/SDL/issues/16255)
  - **Motiv:** Integrare vizuală, documentație sau întrebare de utilizare/testare; impact imediat limitat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-09-06 16:13:36 UTC.

- [ ] [#16254 — \[feature\] open folder in file browser](https://github.com/libsdl-org/SDL/issues/16254)
  - **Motiv:** Cerere de API/capabilitate nouă, reorganizare sau convenție; nu este demonstrată o urgență în funcționalitatea existentă.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-09-06 20:52:55 UTC.

- [ ] [#16248 — GPU: GPUBuffer \<-\> GPUTexture copies?](https://github.com/libsdl-org/SDL/issues/16248)
  - **Motiv:** Integrare vizuală, documentație sau întrebare de utilizare/testare; impact imediat limitat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.4.18` · Actualizat: 2026-09-04 17:59:04 UTC.

- [ ] [#16221 — \[Feature Request\] SInput hint for none-standard VID:PID override](https://github.com/libsdl-org/SDL/issues/16221)
  - **Motiv:** Cerere de API/capabilitate nouă, reorganizare sau convenție; nu este demonstrată o urgență în funcționalitatea existentă.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-08-31 07:46:33 UTC.

- [ ] [#16215 — GPU Multiview](https://github.com/libsdl-org/SDL/issues/16215)
  - **Motiv:** Cerere de API/capabilitate nouă, reorganizare sau convenție; nu este demonstrată o urgență în funcționalitatea existentă.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-09-03 03:07:06 UTC.

- [ ] [#16176 — Review JNI interfaces and maybe migrate to SDLCommandHandler?](https://github.com/libsdl-org/SDL/issues/16176)
  - **Motiv:** Cerere de API/capabilitate nouă, reorganizare sau convenție; nu este demonstrată o urgență în funcționalitatea existentă.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-09-02 09:36:43 UTC.

- [ ] [#16157 — Add Google Play Games on PC detection code](https://github.com/libsdl-org/SDL/issues/16157)
  - **Motiv:** Cerere de API/capabilitate nouă, reorganizare sau convenție; nu este demonstrată o urgență în funcționalitatea existentă.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-08-15 17:32:07 UTC.

- [ ] [#16145 — Function typedefs should have userdata as its first argument](https://github.com/libsdl-org/SDL/issues/16145)
  - **Motiv:** Cerere de API/capabilitate nouă, reorganizare sau convenție; nu este demonstrată o urgență în funcționalitatea existentă.
  - **GitHub:** OPEN · Etichete: — · Milestone: `4.x` · Actualizat: 2026-08-13 16:45:15 UTC.

- [ ] [#16101 — Remove SDL\_IsPhone, IsTV & IsTablet](https://github.com/libsdl-org/SDL/issues/16101)
  - **Motiv:** Cerere de API/capabilitate nouă, reorganizare sau convenție; nu este demonstrată o urgență în funcționalitatea existentă.
  - **GitHub:** OPEN · Etichete: — · Milestone: `4.x` · Actualizat: 2026-08-02 15:35:39 UTC.

- [ ] [#16089 — File extension macro in CategorySharedObject](https://github.com/libsdl-org/SDL/issues/16089)
  - **Motiv:** Cerere de API/capabilitate nouă, reorganizare sau convenție; nu este demonstrată o urgență în funcționalitatea existentă.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-07-31 17:41:41 UTC.

- [ ] [#16066 — iPhone haptics](https://github.com/libsdl-org/SDL/issues/16066)
  - **Motiv:** Cerere de API/capabilitate nouă, reorganizare sau convenție; nu este demonstrată o urgență în funcționalitatea existentă.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-07-29 12:15:27 UTC.

- [ ] [#16062 — Link SDL with EGL statically?](https://github.com/libsdl-org/SDL/issues/16062)
  - **Motiv:** Cerere de API/capabilitate nouă, reorganizare sau convenție; nu este demonstrată o urgență în funcționalitatea existentă.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-07-28 06:26:48 UTC.

- [ ] [#16053 — SDL2 testtimer query](https://github.com/libsdl-org/SDL/issues/16053)
  - **Motiv:** Integrare vizuală, documentație sau întrebare de utilizare/testare; impact imediat limitat.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-07-24 12:30:30 UTC.

- [ ] [#16042 — Keep Native Window Border While Hiding the Title Bar](https://github.com/libsdl-org/SDL/issues/16042)
  - **Motiv:** Cerere de API/capabilitate nouă, reorganizare sau convenție; nu este demonstrată o urgență în funcționalitatea existentă.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-07-27 05:15:32 UTC.

- [ ] [#16022 — Add hint to pass extra devices to libusb whitelist](https://github.com/libsdl-org/SDL/issues/16022)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-07-18 19:53:52 UTC.

- [ ] [#16012 — SDL\_Framework IOS](https://github.com/libsdl-org/SDL/issues/16012)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-07-26 17:42:22 UTC.

- [ ] [#15994 — SDL\_BeginGPURenderPass2](https://github.com/libsdl-org/SDL/issues/15994)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-26 20:07:08 UTC.

- [ ] [#15989 — Add SDL\_shadercross to documentation](https://github.com/libsdl-org/SDL/issues/15989)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-26 20:08:51 UTC.

- [ ] [#15974 — \[Feature Request\] Support trackpad as touch in Windows and Linux, matching \`SDL\_HINT\_TRACKPAD\_IS\_TOUCH\_ONLY\` behavior](https://github.com/libsdl-org/SDL/issues/15974)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-07-11 15:37:06 UTC.

- [ ] [#15963 — Nintendo Switch 2 Pro Controller Bluetooth Implementation](https://github.com/libsdl-org/SDL/issues/15963)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-08-27 02:31:26 UTC.

- [ ] [#15943 — \[GPU\] SDL\_GPUColorTargetBlendState padding is larger than necessary](https://github.com/libsdl-org/SDL/issues/15943)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `4.x` · Actualizat: 2026-07-26 20:23:04 UTC.

- [ ] [#15926 — Trackpad haptics on new Steam Controller](https://github.com/libsdl-org/SDL/issues/15926)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-07-05 12:46:37 UTC.

- [ ] [#15919 — \[Feature Request\] \`SDL\_GetCurrentThreadName\` or similar](https://github.com/libsdl-org/SDL/issues/15919)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-09 20:43:54 UTC.

- [ ] [#15911 — Add SDL\_SetRenderLogicalOffset](https://github.com/libsdl-org/SDL/issues/15911)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-04 14:21:34 UTC.

- [ ] [#15893 — SDL\_IOStream backed by stdin / stdout / stderr](https://github.com/libsdl-org/SDL/issues/15893)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-09-03 09:08:42 UTC.

- [ ] [#15879 — Docs: high-DPI guidance is unclear for exclusive fullscreen (esp. on Wayland)](https://github.com/libsdl-org/SDL/issues/15879)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-07-05 16:24:36 UTC.

- [ ] [#15854 — SDL\_HINT\_ORIENTATIONS to be set after initialized](https://github.com/libsdl-org/SDL/issues/15854)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: — · Actualizat: 2026-06-19 10:49:01 UTC.

- [ ] [#15840 — Possibly preseed Linux CMake cache...](https://github.com/libsdl-org/SDL/issues/15840)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 22:42:30 UTC.

- [ ] [#15836 — Qt + SDL integration demo](https://github.com/libsdl-org/SDL/issues/15836)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-19 03:02:23 UTC.

- [ ] [#15811 — Implement audio device streams](https://github.com/libsdl-org/SDL/issues/15811)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-12 18:52:28 UTC.

- [ ] [#15729 — feature request: ability to select a sound file for controller vibration.](https://github.com/libsdl-org/SDL/issues/15729)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-31 21:19:49 UTC.

- [ ] [#15728 — Suggestion: Add SDL\_realpath() to SDL\_stdinc.h or w/e...](https://github.com/libsdl-org/SDL/issues/15728)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-03 08:00:00 UTC.

- [ ] [#15674 — Fire TV Bluetooth Remote Support](https://github.com/libsdl-org/SDL/issues/15674)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-23 14:59:51 UTC.

- [ ] [#15602 — Add SDL\_GetMousePowerInfo / SDL\_GetKeyboardPowerInfo for wireless peripheral battery](https://github.com/libsdl-org/SDL/issues/15602)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-15 15:56:15 UTC.

- [ ] [#15592 — Button Z and C to \`SDL\_GamepadButton\` standard](https://github.com/libsdl-org/SDL/issues/15592)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-15 15:23:08 UTC.

- [ ] [#15576 — \[Refactoring\] Delegate iostream and filesystem functions to platform-specific files and functions](https://github.com/libsdl-org/SDL/issues/15576)
  - **Motiv:** Capabilitate/API nou, documentație, demonstrație sau refactorizare; nu este demonstrată o urgență în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 20:24:43 UTC.

- [ ] [#15481 — Suggesting a \`SDL\_WaitForMainThreadTasks\` API](https://github.com/libsdl-org/SDL/issues/15481)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 20:29:08 UTC.

- [ ] [#15475 — Incorrect parameter name in Remarks for indexed draw pages](https://github.com/libsdl-org/SDL/issues/15475)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 19:20:49 UTC.

- [ ] [#15461 — \[Feature request\] Single application instance API](https://github.com/libsdl-org/SDL/issues/15461)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-28 07:39:53 UTC.

- [ ] [#15423 — Suggestion: Example comparing original SDL\_PollEvent/main with newer callbacks](https://github.com/libsdl-org/SDL/issues/15423)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-20 21:44:57 UTC.

- [ ] [#15408 — Support direct framebuffer access while double-buffering](https://github.com/libsdl-org/SDL/issues/15408)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-20 17:56:02 UTC.

- [ ] [#15395 — Support display modes with non-square pixels](https://github.com/libsdl-org/SDL/issues/15395)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-20 17:11:50 UTC.

- [ ] [#15388 — Support for static and dynamic palettes with window framebuffers](https://github.com/libsdl-org/SDL/issues/15388)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-20 16:15:04 UTC.

- [ ] [#15361 — \[Feature request\] Anti-aliasing support for SDL\_Renderer](https://github.com/libsdl-org/SDL/issues/15361)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-12 14:48:30 UTC.

- [ ] [#15349 — Not an issue: SDL\_gpu with Vulkan on macOS](https://github.com/libsdl-org/SDL/issues/15349)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-07-20 17:20:05 UTC.

- [ ] [#15328 — Android: Allow creation of multiple windows](https://github.com/libsdl-org/SDL/issues/15328)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-06 01:08:34 UTC.

- [ ] [#15310 — Add proper support for \`ANGLE\` on \`iOS\`.](https://github.com/libsdl-org/SDL/issues/15310)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-20 16:57:20 UTC.

- [ ] [#15253 — gpu: Add OpenXR support for Metal backend](https://github.com/libsdl-org/SDL/issues/15253)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-09 04:15:52 UTC.

- [ ] [#15246 — Additional tray icon features](https://github.com/libsdl-org/SDL/issues/15246)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.8.0` · Actualizat: 2026-07-31 16:26:08 UTC.

- [ ] [#15240 — GPU: Integrate VK\_KHR\_device\_fault](https://github.com/libsdl-org/SDL/issues/15240)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-20 14:02:41 UTC.

- [ ] [#15238 — Any demo to use SDL3 on qt for android？](https://github.com/libsdl-org/SDL/issues/15238)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-17 04:08:46 UTC.

- [ ] [#15219 — SDL\_MessageBoxData::colorScheme has wrong naming convention](https://github.com/libsdl-org/SDL/issues/15219)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `4.x` · Actualizat: 2026-03-16 22:51:49 UTC.

- [ ] [#15201 — feature request: have access to the steam controllers gyro directly](https://github.com/libsdl-org/SDL/issues/15201)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 22:19:58 UTC.

- [ ] [#15181 — GPU: Add transparent window support](https://github.com/libsdl-org/SDL/issues/15181)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 22:20:07 UTC.

- [ ] [#15164 — Întrebare SDL\_GPU: încărcarea eficientă a resurselor în background fără blocarea randării](https://github.com/libsdl-org/SDL/issues/15164)
  - Rezumat editorial; titlul integral este disponibil în issue.
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 22:21:48 UTC.

- [ ] [#15146 — Feature request: make types clickable in documentation](https://github.com/libsdl-org/SDL/issues/15146)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 22:26:13 UTC.

- [ ] [#15134 — Extended Web Game Controller Support](https://github.com/libsdl-org/SDL/issues/15134)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-17 08:32:21 UTC.

- [ ] [#15126 — SDL\_reinterpret\_cast could function better in C](https://github.com/libsdl-org/SDL/issues/15126)
  - **Motiv:** Extensie, exemplu, documentație sau întrebare de integrare; nu este demonstrată o urgență în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-28 05:44:40 UTC.

- [ ] [#15070 — filesystem: Add a file watcher API](https://github.com/libsdl-org/SDL/issues/15070)
  - **Motiv:** Extensie/API nou, documentație, exemplu sau clarificare de utilizare; nu există urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-05-12 04:46:52 UTC.

- [ ] [#15065 — Convenience Functions to Convert Between SDL\_PixelFormat and Vulkan Formats](https://github.com/libsdl-org/SDL/issues/15065)
  - **Motiv:** Extensie/API nou, documentație, exemplu sau clarificare de utilizare; nu există urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-24 00:09:50 UTC.

- [ ] [#15036 — OpenGL: Investigate WGL\_NV\_DX\_interop2 integration](https://github.com/libsdl-org/SDL/issues/15036)
  - **Motiv:** Extensie/API nou, documentație, exemplu sau clarificare de utilizare; nu există urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 22:33:42 UTC.

- [ ] [#15028 — Adding a window flag to set "input transparency" on windows?](https://github.com/libsdl-org/SDL/issues/15028)
  - **Motiv:** Extensie/API nou, documentație, exemplu sau clarificare de utilizare; nu există urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 18:24:09 UTC.

- [ ] [#15017 — Feature Request: Access to native Vulkan handles from SDL\_GPUDevice properties](https://github.com/libsdl-org/SDL/issues/15017)
  - **Motiv:** Extensie/API nou, documentație, exemplu sau clarificare de utilizare; nu există urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-02-10 15:56:44 UTC.

- [ ] [#15013 — Implement a way to be able use \`AChoreographer\` on \`Android\`.](https://github.com/libsdl-org/SDL/issues/15013)
  - **Motiv:** Extensie/API nou, documentație, exemplu sau clarificare de utilizare; nu există urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.8.0` · Actualizat: 2026-06-16 22:35:05 UTC.

- [ ] [#14939 — ETC2\_RGB8A8 image format](https://github.com/libsdl-org/SDL/issues/14939)
  - **Motiv:** Extensie/API nou, documentație, exemplu sau clarificare de utilizare; nu există urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-02-01 00:02:40 UTC.

- [ ] [#14889 — Expose a standardized set of bindings for instruments](https://github.com/libsdl-org/SDL/issues/14889)
  - **Motiv:** Extensie/API nou, documentație, exemplu sau clarificare de utilizare; nu există urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-05 07:44:42 UTC.

- [ ] [#14829 — input-gamepad-events example assumes Xbox style controller](https://github.com/libsdl-org/SDL/issues/14829)
  - **Motiv:** Extensie/API nou, documentație, exemplu sau clarificare de utilizare; nu există urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 22:43:59 UTC.

- [ ] [#14809 — GPU: STORAGE\_READ vs SAMPLER](https://github.com/libsdl-org/SDL/issues/14809)
  - **Motiv:** Extensie/API nou, documentație, exemplu sau clarificare de utilizare; nu există urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-05-24 15:44:12 UTC.

- [ ] [#14774 — Write docs on building for 32-bit Linux from 64-bit host.](https://github.com/libsdl-org/SDL/issues/14774)
  - **Motiv:** Extensie/API nou, documentație, exemplu sau clarificare de utilizare; nu există urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-01-08 19:21:46 UTC.

- [ ] [#14708 — Microsoft SideWinder Freestyle Pro gamepad support](https://github.com/libsdl-org/SDL/issues/14708)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-27 18:28:25 UTC.

- [ ] [#14675 — How to adjust the default parameter settings for a specific gamepad in Steam?](https://github.com/libsdl-org/SDL/issues/14675)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-23 18:19:33 UTC.

- [ ] [#14673 — \[Feature Request\] Support XEmbed on X11 for plugin GUIs (e.g. VST3, CLAP)](https://github.com/libsdl-org/SDL/issues/14673)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-18 22:19:54 UTC.

- [ ] [#14650 — \[Desktop-Specific Feature Request\] Get Icon Pixel Data from File or Directory Path](https://github.com/libsdl-org/SDL/issues/14650)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-07-04 00:06:29 UTC.

- [ ] [#14633 — Nice to have: NFC and fingerprint](https://github.com/libsdl-org/SDL/issues/14633)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-02 19:59:34 UTC.

- [ ] [#14592 — C99ify the test programs.](https://github.com/libsdl-org/SDL/issues/14592)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-04 18:34:40 UTC.

- [ ] [#14585 — \[feature request\] native-like wider resize handle for borderless (win32)](https://github.com/libsdl-org/SDL/issues/14585)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-04 02:39:43 UTC.

- [ ] [#14560 — GPU: Feature request for unorm10-10-10-2 vertex input format](https://github.com/libsdl-org/SDL/issues/14560)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.8.0` · Actualizat: 2026-06-17 12:34:31 UTC.

- [ ] [#14546 — SDL Tray is missing a notification of menu being opened/closed](https://github.com/libsdl-org/SDL/issues/14546)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-09-06 20:06:33 UTC.

- [ ] [#14498 — pen: Implement WinTab support for Windows.](https://github.com/libsdl-org/SDL/issues/14498)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 17:45:57 UTC.

- [ ] [#14439 — SDL\_EnumeratePropertiesCallback should return SDL\_EnumerationResult](https://github.com/libsdl-org/SDL/issues/14439)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `4.x` · Actualizat: 2025-11-10 17:10:23 UTC.

- [ ] [#14409 — Enscripten: support SDL\_HINT\_ORIENTATIONS](https://github.com/libsdl-org/SDL/issues/14409)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2025-11-06 23:28:31 UTC.

- [ ] [#14395 — DISCUSSION: how should "toolkit" functionality be handled from now on?](https://github.com/libsdl-org/SDL/issues/14395)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2025-11-18 18:26:49 UTC.

- [ ] [#14382 — Windows 9x support](https://github.com/libsdl-org/SDL/issues/14382)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-07-24 06:48:53 UTC.

- [ ] [#14342 — \[Feature Request\] Add property for allocating extra cycles for GPU API resources](https://github.com/libsdl-org/SDL/issues/14342)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-02 13:22:06 UTC.

- [ ] [#14230 — Change how we deal with OpenGL context attributes](https://github.com/libsdl-org/SDL/issues/14230)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `4.x` · Actualizat: 2026-06-16 23:00:30 UTC.

- [ ] [#14180 — OpenGL context without an SDL\_Window.](https://github.com/libsdl-org/SDL/issues/14180)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 16:16:05 UTC.

- [ ] [#14156 — \`SDL\_GetSurfaceClipRect\` surface argument is not const](https://github.com/libsdl-org/SDL/issues/14156)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `4.x` · Actualizat: 2025-10-06 01:27:08 UTC.

- [ ] [#14078 — Replace D3D12, Metal, and Vulkan renderers with the GPU renderer](https://github.com/libsdl-org/SDL/issues/14078)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-07 18:33:20 UTC.

- [ ] [#13986 — Feature request: API to get paths for cache folder and preferences folder](https://github.com/libsdl-org/SDL/issues/13986)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 23:10:24 UTC.

- [ ] [#13985 — Implement SDL\_ShowOpenDialog functions on emscripten](https://github.com/libsdl-org/SDL/issues/13985)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-27 10:08:04 UTC.

- [ ] [#13873 — SDL3 forces system theme ](https://github.com/libsdl-org/SDL/issues/13873)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2025-09-14 23:02:33 UTC.

- [ ] [#13851 — Support Linux IIO devices under SDL\_SENSORS API](https://github.com/libsdl-org/SDL/issues/13851)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-02 15:43:04 UTC.

- [ ] [#13786 — Dual Source Blending?](https://github.com/libsdl-org/SDL/issues/13786)
  - **Motiv:** Extensie de capabilitate/API, documentație, reorganizare sau întrebare; nu este stabilită o urgență a contractului existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.8.0` · Actualizat: 2026-06-16 18:11:29 UTC.

- [ ] [#13763 — Wayland: extreme lag when resizing window](https://github.com/libsdl-org/SDL/issues/13763)
  - **Motiv:** Urmărire externă: conform contributorului, fixul SDL există deja și se așteaptă o versiune libdecor.
  - **GitHub:** OPEN · Etichete: `notourbug` · Milestone: `3.x` · Actualizat: 2026-08-11 05:31:32 UTC.
  - **Context:** Issue-ul rămâne deschis pentru vizibilitate; în comentariul consultat nu mai este indicat lucru de făcut în SDL. [Discuție](https://github.com/libsdl-org/SDL/issues/13763#issuecomment-3262440315).

- [ ] [#13379 — wayland: set content type](https://github.com/libsdl-org/SDL/issues/13379)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-07-17 13:58:58 UTC.

- [ ] [#13370 — SDL\_Render (Clamp to) Border Texture Address Mode](https://github.com/libsdl-org/SDL/issues/13370)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-07-21 07:49:59 UTC.

- [ ] [#13334 — SDLFragment](https://github.com/libsdl-org/SDL/issues/13334)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-06 14:24:54 UTC.

- [ ] [#13313 — N3DS: Not calling gfxInitDefault](https://github.com/libsdl-org/SDL/issues/13313)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-21 08:06:16 UTC.

- [ ] [#13302 — Support for drag-and-drop in Android](https://github.com/libsdl-org/SDL/issues/13302)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 13:38:59 UTC.

- [ ] [#13297 — Use \`clock\_gettime\_nsec\_np(CLOCK\_UPTIME\_RAW)\` instead of \`mach\_absolute\_time()\` on Apple platforms](https://github.com/libsdl-org/SDL/issues/13297)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 13:41:41 UTC.

- [ ] [#13237 — How to launch an SDL3 game via a launcher on iOS](https://github.com/libsdl-org/SDL/issues/13237)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 13:53:21 UTC.

- [ ] [#13102 — Missing endianness independent pixel formats](https://github.com/libsdl-org/SDL/issues/13102)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-05-23 16:22:46 UTC.

- [ ] [#13041 — Convert platform dependent keycode to SDL Keycode/Scancodethrough an API](https://github.com/libsdl-org/SDL/issues/13041)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-27 15:31:21 UTC.

- [ ] [#13031 — SDL\_ResumeAudioStreamDevice naming](https://github.com/libsdl-org/SDL/issues/13031)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `4.x` · Actualizat: 2025-05-14 17:20:13 UTC.

- [ ] [#13024 — Extend Audio interface to support Xbox One headset bringup](https://github.com/libsdl-org/SDL/issues/13024)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-27 20:47:50 UTC.

- [ ] [#12997 — Retrieve \`SDL\_GamepadHasSensor\` with Steam Input](https://github.com/libsdl-org/SDL/issues/12997)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-05-29 00:41:28 UTC.

- [ ] [#12966 — Will SDL\_Renderer ever support vertex shader uniforms or programmable vertex shading?](https://github.com/libsdl-org/SDL/issues/12966)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-05-06 22:59:46 UTC.

- [ ] [#12958 — Updating sdl3 migration guide on SDL\_GL\_GetDrawableSize()](https://github.com/libsdl-org/SDL/issues/12958)
  - **Motiv:** Capabilitate nouă, modernizare, documentație sau întrebare de utilizare; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-05-05 22:18:31 UTC.

- [ ] [#12902 — \[Emscripten\] Building with RelWithDebInfo and Tests/Examples prints a lot of DWARF optimization warnings](https://github.com/libsdl-org/SDL/issues/12902)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-28 17:11:25 UTC.

- [ ] [#12803 — D3D11 UWP swapchain requirements do not reflect DXGI 1.4 capability](https://github.com/libsdl-org/SDL/issues/12803)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-22 17:06:45 UTC.

- [ ] [#12788 — SDL3 feature request: create OpenGL contexts detached from windows](https://github.com/libsdl-org/SDL/issues/12788)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-27 20:47:09 UTC.

- [ ] [#12755 — \[SDL3\] Add SDL\_GetPathInfoWithProperties](https://github.com/libsdl-org/SDL/issues/12755)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-07 17:48:16 UTC.

- [ ] [#12740 — Unclear documentation about \`enable\_depth\_clip\` in \`SDL\_GPURasterizerState\`](https://github.com/libsdl-org/SDL/issues/12740)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-27 03:09:52 UTC.

- [ ] [#12726 — SDL3 feature: Compact decoration hint/flag](https://github.com/libsdl-org/SDL/issues/12726)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-03 15:35:01 UTC.

- [ ] [#12688 — Getting the keystate of a specific keyboard](https://github.com/libsdl-org/SDL/issues/12688)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-04 23:44:56 UTC.

- [ ] [#12687 — SDL3 Feature - Power State change event](https://github.com/libsdl-org/SDL/issues/12687)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-31 15:34:35 UTC.

- [ ] [#12683 — No way of creating a window which does not accept mouse inputs/events (click-through) but isn't totally transparent/invisible(?)](https://github.com/libsdl-org/SDL/issues/12683)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-11-23 02:13:30 UTC.

- [ ] [#12670 — GPU: Allow multisampled texture sampling](https://github.com/libsdl-org/SDL/issues/12670)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-16 19:10:12 UTC.

- [ ] [#12655 — GPU: Feature request - Functions for \`SDL\_GPUVertexElementFormat\` which retrieve size of its actual size, etc](https://github.com/libsdl-org/SDL/issues/12655)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-27 03:09:17 UTC.

- [ ] [#12615 — \[Process\] \[New Feature\] Identifying current process](https://github.com/libsdl-org/SDL/issues/12615)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 16:09:20 UTC.

- [ ] [#12524 — Expose a wrapper around SDL\_QuitMainCallbacks to allow early exit when using callbacks](https://github.com/libsdl-org/SDL/issues/12524)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 14:45:15 UTC.

- [ ] [#12512 — Creating Mutliple Windows not possible on Emscripten](https://github.com/libsdl-org/SDL/issues/12512)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-27 20:41:37 UTC.

- [ ] [#12482 — SDL\_SetClipboardData() requires the video subsystem and event handling](https://github.com/libsdl-org/SDL/issues/12482)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-06 16:14:28 UTC.

- [ ] [#12406 — SDL3 lacks the functionality to force landscape mode and restore portrait mode on mobile devices.](https://github.com/libsdl-org/SDL/issues/12406)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-02-27 04:12:22 UTC.

- [ ] [#12391 — Source aspect ratio information missing in TouchFingerEvent generated by trackpads](https://github.com/libsdl-org/SDL/issues/12391)
  - **Motiv:** Extensie/API, documentație sau diagnostic de build; fără urgență demonstrată.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-06-16 15:10:17 UTC.

- [ ] [#12321 — SDL3 Proposal: Force touch trackpad](https://github.com/libsdl-org/SDL/issues/12321)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-02-18 16:50:57 UTC.

- [ ] [#12311 — Fragment shader should be optional in SDL\_gpu graphics pipeline](https://github.com/libsdl-org/SDL/issues/12311)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:04:52 UTC.

- [ ] [#12308 — SDL3 Examples source code cannot be copied with Ctrl-C](https://github.com/libsdl-org/SDL/issues/12308)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-02-28 06:08:25 UTC.

- [ ] [#12261 — Add a "Best Practices" page for HighDPI](https://github.com/libsdl-org/SDL/issues/12261)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-07-25 12:51:33 UTC.

- [ ] [#12237 — Shader language guide](https://github.com/libsdl-org/SDL/issues/12237)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:07:32 UTC.

- [ ] [#12222 — SDL\_Surface: lossless pixel art rotation](https://github.com/libsdl-org/SDL/issues/12222)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-02-23 09:58:02 UTC.

- [ ] [#12167 — Supporting Joystick Colors (Joycons + Pro Controller)](https://github.com/libsdl-org/SDL/issues/12167)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-02-07 05:15:18 UTC.

- [ ] [#12124 — Integrate SDL\_AsyncIO with SDL\_Storage](https://github.com/libsdl-org/SDL/issues/12124)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-26 22:38:02 UTC.

- [ ] [#12087 — Merge OpenGL renderers...](https://github.com/libsdl-org/SDL/issues/12087)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-27 19:59:53 UTC.

- [ ] [#12063 — Add note about checking SDL\_CLIPBOARDUPDATE in Wiki CategoryClipboard before calling SDL\_GetClipboardText()](https://github.com/libsdl-org/SDL/issues/12063)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-02-02 00:05:04 UTC.

- [ ] [#12028 — SDL GPU: Add a way to enable GPU based validation](https://github.com/libsdl-org/SDL/issues/12028)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-27 03:08:34 UTC.

- [ ] [#12008 — SDL3, macOS: Deprecation warnings when building with Xcode](https://github.com/libsdl-org/SDL/issues/12008)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:26:41 UTC.

- [ ] [#11890 — Android: \`SDLActivity\` being an activity prevents activities from inheriting other classes](https://github.com/libsdl-org/SDL/issues/11890)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-08 21:20:37 UTC.

- [ ] [#11856 — Replace/extend/add SDL3's software renderer by Blend2D](https://github.com/libsdl-org/SDL/issues/11856)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-13 22:42:23 UTC.

- [ ] [#11832 — SDL\_IO\* Buffering Mode?](https://github.com/libsdl-org/SDL/issues/11832)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-04 20:44:15 UTC.

- [ ] [#11755 — Post-3.2.0 Raw Event Rework](https://github.com/libsdl-org/SDL/issues/11755)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:32:41 UTC.

- [ ] [#11696 — \[SDL3\] GPU: Investigate adding a Query API](https://github.com/libsdl-org/SDL/issues/11696)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: `enhancement` · Milestone: `3.6.0` · Actualizat: 2026-08-20 15:00:40 UTC.

- [ ] [#11637 — C26819 Warning in Visual Studio with SDL\_stdinc.h file](https://github.com/libsdl-org/SDL/issues/11637)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:34:56 UTC.

- [ ] [#11636 — Expose OS accessibility preferences?](https://github.com/libsdl-org/SDL/issues/11636)
  - **Motiv:** Extensie/API, documentație, reorganizare sau avertismente; nu impact critic demonstrat.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-14 05:51:46 UTC.

- [ ] [#11634 — Any way of compiling for iOS with Theos on Linux?](https://github.com/libsdl-org/SDL/issues/11634)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:36:05 UTC.

- [ ] [#11588 — AsyncIO: SDL\_AsyncIOFromFile could be asynchronous?](https://github.com/libsdl-org/SDL/issues/11588)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-04 09:20:37 UTC.

- [ ] [#11570 — \[SDL3\] Proposal: File System Events](https://github.com/libsdl-org/SDL/issues/11570)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-26 23:16:04 UTC.

- [ ] [#11547 — SDL\_storage: Streaming file I/O?](https://github.com/libsdl-org/SDL/issues/11547)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-07-11 00:31:30 UTC.

- [ ] [#11545 — SDL DisplayID to GPU map RFC](https://github.com/libsdl-org/SDL/issues/11545)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-06-16 15:24:01 UTC.

- [ ] [#11489 — SDL\_opengl.h being no-op on iOS is unintuitive](https://github.com/libsdl-org/SDL/issues/11489)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 19:56:26 UTC.

- [ ] [#11452 — GPU: Integrating Profilers](https://github.com/libsdl-org/SDL/issues/11452)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-10-17 14:58:53 UTC.

- [ ] [#11404 — Android: \`ASensorManager\_getInstance()\` deprecated since API level 26](https://github.com/libsdl-org/SDL/issues/11404)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 19:43:04 UTC.

- [ ] [#11368 — SDL3 Proposal: Title/user open-storage functions can create containers rooted relative to their default/overridden root](https://github.com/libsdl-org/SDL/issues/11368)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-03-27 22:35:28 UTC.

- [ ] [#11362 — Adding support for more types of controllers (arcade, gamecube, n64, sega, etc.)](https://github.com/libsdl-org/SDL/issues/11362)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:51:14 UTC.

- [ ] [#11340 — SDL3: Recursive SDL\_GlobDirectory() support (\*\*)](https://github.com/libsdl-org/SDL/issues/11340)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:52:15 UTC.

- [ ] [#11276 — SDL\_RenderGeometryRaw: optionally copy additional coordinates based on stride](https://github.com/libsdl-org/SDL/issues/11276)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-27 23:55:24 UTC.

- [ ] [#11264 — Emscripten: Support running SDL programs in a web worker](https://github.com/libsdl-org/SDL/issues/11264)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-24 00:42:13 UTC.

- [ ] [#11226 — SDL\_PowerInfo() should take a pointer to SDL\_DateTime](https://github.com/libsdl-org/SDL/issues/11226)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-16 04:26:47 UTC.

- [ ] [#11178 — Native window types](https://github.com/libsdl-org/SDL/issues/11178)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-21 15:56:32 UTC.

- [ ] [#11067 — Fcitx development packages not required to build](https://github.com/libsdl-org/SDL/issues/11067)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-21 14:17:45 UTC.

- [ ] [#11022 — wikiheaders: format parameters consistently](https://github.com/libsdl-org/SDL/issues/11022)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-11 15:48:26 UTC.

- [ ] [#11010 — Unify shared library loading](https://github.com/libsdl-org/SDL/issues/11010)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 18:46:47 UTC.

- [ ] [#10904 — GPU: Add support for SM7 SPIR-V](https://github.com/libsdl-org/SDL/issues/10904)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: `enhancement` · Milestone: `3.x` · Actualizat: 2024-09-19 19:36:48 UTC.

- [ ] [#10887 — Audio Feature request: SDL\_SetAudioStreamGainChannelMap, SDL\_GetAudioStreamGainChannelMap](https://github.com/libsdl-org/SDL/issues/10887)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 19:44:46 UTC.

- [ ] [#10876 — GPU: Access to platform-specific objects](https://github.com/libsdl-org/SDL/issues/10876)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-11-12 05:58:28 UTC.

- [ ] [#10849 — GPU: Fragment Storage (Buffer) Writes?](https://github.com/libsdl-org/SDL/issues/10849)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-09 23:22:39 UTC.

- [ ] [#10841 — SDL\_filesystem: get temporary folder](https://github.com/libsdl-org/SDL/issues/10841)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.8.0` · Actualizat: 2026-06-16 19:57:08 UTC.

- [ ] [#10768 — \[Feature Request\] SDL3 GPU Backend for WebGPU Target](https://github.com/libsdl-org/SDL/issues/10768)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-07-03 13:41:35 UTC.

- [ ] [#10757 — SDL3: SDL\_assert should have optional error message](https://github.com/libsdl-org/SDL/issues/10757)
  - **Motiv:** Extensie, integrare, documentație sau refactorizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 20:40:56 UTC.

- [ ] [#10448 — Interactive drag and drop api ideas](https://github.com/libsdl-org/SDL/issues/10448)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 20:36:52 UTC.

- [ ] [#10388 — \`SDL\_GetWindowSizeInPixels\` may fail](https://github.com/libsdl-org/SDL/issues/10388)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 20:38:39 UTC.

- [ ] [#10359 — \[SDL3\]\[audio\] time to drop hardcoded channel maps for good?](https://github.com/libsdl-org/SDL/issues/10359)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-27 20:35:20 UTC.

- [ ] [#10350 — The SDL3 Examples Megathread](https://github.com/libsdl-org/SDL/issues/10350)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-09-07 14:00:17 UTC.

- [ ] [#10337 — device event filter system](https://github.com/libsdl-org/SDL/issues/10337)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-08-10 15:46:35 UTC.

- [ ] [#10179 — \[testffmpeg\] Is it possible to render the frame decoded by nvdec?](https://github.com/libsdl-org/SDL/issues/10179)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-07-08 03:48:56 UTC.

- [ ] [#10160 — Wishlist: Frame Pacing Subsystem](https://github.com/libsdl-org/SDL/issues/10160)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-01-12 09:48:54 UTC.

- [ ] [#10148 — New API request: \`SDL\_ConvertSurfaceToPixels\`](https://github.com/libsdl-org/SDL/issues/10148)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-06-30 17:22:22 UTC.

- [ ] [#10138 — Implement SDL\_EVENT\_TEXT\_EDITING\_CANDIDATES for fcitx and ibus IMEs](https://github.com/libsdl-org/SDL/issues/10138)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-21 14:18:47 UTC.

- [ ] [#9949 — \[proposal\] Remove all usages of \`check\_symbol\_exists\`](https://github.com/libsdl-org/SDL/issues/9949)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-04 18:08:01 UTC.

- [ ] [#9847 — Single channel alpha formats](https://github.com/libsdl-org/SDL/issues/9847)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-07-05 21:30:38 UTC.

- [ ] [#9837 — Is there any plan to support HarmonyOS?](https://github.com/libsdl-org/SDL/issues/9837)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-07-28 00:29:35 UTC.

- [ ] [#9826 — Add SDL\_AcquireCameraFrame as SDL\_Texture 0-copy texture.](https://github.com/libsdl-org/SDL/issues/9826)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-05-22 18:18:10 UTC.

- [ ] [#9771 — \[SDL3\] C++ headers & modules](https://github.com/libsdl-org/SDL/issues/9771)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-03-07 20:09:55 UTC.

- [ ] [#9657 — Feature Request: File pickers on UIKit and Android](https://github.com/libsdl-org/SDL/issues/9657)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-05-13 21:10:17 UTC.

- [ ] [#9590 — \[Request\] Native menu bars](https://github.com/libsdl-org/SDL/issues/9590)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-01-29 18:54:23 UTC.

- [ ] [#9580 — "Header only" with portable dynamic linking](https://github.com/libsdl-org/SDL/issues/9580)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-05-23 16:14:03 UTC.

- [ ] [#9559 — Add support for frame present protocols](https://github.com/libsdl-org/SDL/issues/9559)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-08 18:46:51 UTC.

- [ ] [#9463 — Request: Add D3D12 support to testffmpeg..](https://github.com/libsdl-org/SDL/issues/9463)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-05-23 16:17:17 UTC.

- [ ] [#9197 — Associate HID controller with audio device](https://github.com/libsdl-org/SDL/issues/9197)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-25 17:05:30 UTC.

- [ ] [#9108 — Future camera API work...](https://github.com/libsdl-org/SDL/issues/9108)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 18:02:41 UTC.

- [ ] [#8912 — Consider adding a function/helper for creating WebGPU surfaces](https://github.com/libsdl-org/SDL/issues/8912)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-08-30 14:41:16 UTC.

- [ ] [#8887 — Android Java code modernization (lots of deprecation warnings)](https://github.com/libsdl-org/SDL/issues/8887)
  - **Motiv:** Extensie/API, documentație, integrare sau modernizare; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-01-20 13:24:10 UTC.

- [ ] [#8559 — Drag and drop improvements](https://github.com/libsdl-org/SDL/issues/8559)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-11-25 10:40:27 UTC.

- [ ] [#8398 — Add multi-sampling for DirectX](https://github.com/libsdl-org/SDL/issues/8398)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-07 17:29:10 UTC.

- [ ] [#8377 — We need SDL3.0 support render YUVA format (which include alpha channel).](https://github.com/libsdl-org/SDL/issues/8377)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-10-31 16:25:07 UTC.

- [ ] [#8292 — \`ANGLE\` for iOS (looks) ready, and Apple urges devs to migrate away from \`OpenGLES.framework\`. Time for a switch?](https://github.com/libsdl-org/SDL/issues/8292)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-26 17:17:15 UTC.

- [ ] [#8153 — Add support for single-channel colour formats](https://github.com/libsdl-org/SDL/issues/8153)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-05-10 18:10:56 UTC.

- [ ] [#7915 — Add SDL\_basename and SDL\_dirname](https://github.com/libsdl-org/SDL/issues/7915)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-07-08 18:15:37 UTC.

- [ ] [#7798 — Support Vulkan on Haiku](https://github.com/libsdl-org/SDL/issues/7798)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-08-11 19:15:37 UTC.

- [ ] [#7758 — Location API?](https://github.com/libsdl-org/SDL/issues/7758)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-03-12 13:36:50 UTC.

- [ ] [#7706 — Support OS-level pinch/zoom events](https://github.com/libsdl-org/SDL/issues/7706)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-04-03 19:52:00 UTC.

- [ ] [#7576 — SDL3: input monitoring?](https://github.com/libsdl-org/SDL/issues/7576)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-11-08 04:24:23 UTC.

- [ ] [#6979 — Easy way to get a cache patch on Android](https://github.com/libsdl-org/SDL/issues/6979)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-01-03 14:57:15 UTC.

- [ ] [#6831 — RFE: remote desktop protocol support](https://github.com/libsdl-org/SDL/issues/6831)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-11-08 00:43:12 UTC.

- [ ] [#6784 — Cross-platform native video playback support](https://github.com/libsdl-org/SDL/issues/6784)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-05-01 18:12:18 UTC.

- [ ] [#6781 — Idea: Custom platform plugins](https://github.com/libsdl-org/SDL/issues/6781)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-06-04 22:44:05 UTC.

- [ ] [#6742 — Shared Texture Support](https://github.com/libsdl-org/SDL/issues/6742)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-05-04 08:34:19 UTC.

- [ ] [#6555 — Sensor API: expose separate user acceleration and gravity sensor types](https://github.com/libsdl-org/SDL/issues/6555)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-11-19 16:31:55 UTC.

- [ ] [#6553 — Sensor API: allow specifying update rate](https://github.com/libsdl-org/SDL/issues/6553)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-05-27 01:15:14 UTC.

- [ ] [#6540 — Add steering wheel API for SDL3](https://github.com/libsdl-org/SDL/issues/6540)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-08-12 22:37:50 UTC.

- [ ] [#6483 — Feature request: functions that read events from the queue to a given timestamp](https://github.com/libsdl-org/SDL/issues/6483)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-12-21 16:42:16 UTC.

- [ ] [#6410 — Solve antialiasing issues applying alpha bleeding when loading / converting textures](https://github.com/libsdl-org/SDL/issues/6410)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-10-06 17:02:46 UTC.

- [ ] [#6337 — Feature Request: Provide machine readable API definitions with SDL3](https://github.com/libsdl-org/SDL/issues/6337)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2026-04-17 00:17:02 UTC.

- [ ] [#6265 — thread safe SDL\_Renderer](https://github.com/libsdl-org/SDL/issues/6265)
  - **Motiv:** Extensie, integrare/API nou sau redesign; nu urgență demonstrată în contractul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2023-05-09 16:28:39 UTC.

- [ ] [#6085 — \[Feature request\] Add support for SDL\_DROPTEXT on more platforms ?](https://github.com/libsdl-org/SDL/issues/6085)
  - **Motiv:** Extensie/API sau integrare nouă; nu urgență demonstrată în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-10-24 18:06:01 UTC.

- [ ] [#5368 — Emscripten port feature request: Share action](https://github.com/libsdl-org/SDL/issues/5368)
  - **Motiv:** Extensie/API sau integrare nouă; nu urgență demonstrată în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-07-08 17:18:31 UTC.

- [ ] [#5292 — Support for events when dragging a file over the window](https://github.com/libsdl-org/SDL/issues/5292)
  - **Motiv:** Extensie/API sau integrare nouă; nu urgență demonstrată în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-02-07 04:43:00 UTC.

- [ ] [#5238 — Feature Request: Cross Platform Control / GUI Key Switching](https://github.com/libsdl-org/SDL/issues/5238)
  - **Motiv:** Extensie/API sau integrare nouă; nu urgență demonstrată în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-12-07 05:09:49 UTC.

- [ ] [#4710 — Feature request: SDL\_SetRendererGammaRamp(), affecting final SDL\_RenderPresent()](https://github.com/libsdl-org/SDL/issues/4710)
  - **Motiv:** Extensie/API sau integrare nouă; nu urgență demonstrată în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-11-25 17:16:43 UTC.

- [ ] [#4464 — Develop SDL\_ActionSet](https://github.com/libsdl-org/SDL/issues/4464)
  - **Motiv:** Extensie/API sau integrare nouă; nu urgență demonstrată în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2025-06-17 13:01:24 UTC.

- [ ] [#4156 — \[Feature request\] Generate texture mipmap](https://github.com/libsdl-org/SDL/issues/4156)
  - **Motiv:** Extensie/API sau integrare nouă; nu urgență demonstrată în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.6.0` · Actualizat: 2026-08-22 15:16:05 UTC.

- [ ] [#3518 — Support for composite gamepads](https://github.com/libsdl-org/SDL/issues/3518)
  - **Motiv:** Extensie/API sau integrare nouă; nu urgență demonstrată în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2024-05-22 17:40:30 UTC.

- [ ] [#2547 — Suggestion: Dynamic GTK message box when GTK 3 or 2 is available (Working example included)](https://github.com/libsdl-org/SDL/issues/2547)
  - **Motiv:** Extensie/API sau integrare nouă; nu urgență demonstrată în comportamentul existent.
  - **GitHub:** OPEN · Etichete: — · Milestone: `3.x` · Actualizat: 2022-10-25 21:36:47 UTC.

- [ ] [#2440 — Retrieving the default SDL\_MessageBoxColorScheme for all platforms](https://github.com/libsdl-org/SDL/issues/2440)
  - **Motiv:** Extensie/API sau integrare nouă; nu urgență demonstrată în comportamentul existent.
  - **GitHub:** OPEN · Etichete: `enhancement` · Milestone: `3.x` · Actualizat: 2023-11-04 20:32:36 UTC.

- [ ] [#1905 — System Display Type "Console", "Desktop", "Mobile", "HMD"](https://github.com/libsdl-org/SDL/issues/1905)
  - **Motiv:** Extensie/API sau integrare nouă; nu urgență demonstrată în comportamentul existent.
  - **GitHub:** OPEN · Etichete: `enhancement` · Milestone: `3.x` · Actualizat: 2023-11-04 19:21:35 UTC.

- [ ] [#1829 — Extensible Drag and Drop API](https://github.com/libsdl-org/SDL/issues/1829)
  - **Motiv:** Extensie/API sau integrare nouă; nu urgență demonstrată în comportamentul existent.
  - **GitHub:** OPEN · Etichete: `enhancement` · Milestone: `3.x` · Actualizat: 2022-02-08 18:53:05 UTC.

- [ ] [#1419 — Add a function to draw circles](https://github.com/libsdl-org/SDL/issues/1419)
  - **Motiv:** Extensie/API sau integrare nouă; nu urgență demonstrată în comportamentul existent.
  - **GitHub:** OPEN · Etichete: `enhancement` · Milestone: `3.x` · Actualizat: 2026-01-13 22:51:48 UTC.
