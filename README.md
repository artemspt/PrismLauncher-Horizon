<p align="center">
<picture>
  <source media="(prefers-color-scheme: dark)" srcset="/program_info/org.prismlauncher.PrismLauncher.logo-darkmode.svg">
  <source media="(prefers-color-scheme: light)" srcset="/program_info/org.prismlauncher.PrismLauncher.logo.svg">
  <img alt="Prism Launcher Horizon" src="/program_info/org.prismlauncher.PrismLauncher.logo.svg" width="40%">
</picture>
</p>

<p align="center">
  <b>Prism Launcher Horizon</b> is <a href="https://github.com/PrismLauncher/PrismLauncher">Prism Launcher</a>
  that also installs and runs <a href="https://github.com/horizon-rust/horizon">Horizon</a>,
  Minecraft: Java Edition rewritten in Rust.<br /><br />
  It is <b>not</b> Prism Launcher and is not endorsed by or affiliated with the Prism Launcher project.
</p>

<p align="center">
  <a href="https://github.com/artemspt/PrismLauncher-Horizon/releases/latest"><b>⬇ Download the latest release</b></a>
  &nbsp;·&nbsp;
  <a href="https://hammer.veyron.online">Horizon Hammer, the mod core</a>
</p>

## Download

On the [**Releases page**](https://github.com/artemspt/PrismLauncher-Horizon/releases/latest), pick the file for your system:

| System | File |
| --- | --- |
| Linux x86_64 | `PrismLauncher-Linux-x86_64.AppImage`, or `…-Linux-Qt6-Portable-….tar.gz` |
| Linux aarch64 | `PrismLauncher-Linux-aarch64.AppImage`, or `…-Linux-aarch64-Qt6-Portable-….tar.gz` |
| Windows x64 | `…-Windows-MSVC-Setup-….exe` (installer), or `…-Windows-MSVC-Portable-….zip` |
| Windows on ARM | `…-Windows-MSVC-arm64-Setup-….exe`, or `…-Windows-MSVC-arm64-Portable-….zip` |
| macOS (Intel and Apple Silicon) | `…-macOS-….dmg` |

The builds are not signed yet: Windows SmartScreen and macOS Gatekeeper will ask before the first start.

## Playing Horizon

1. Add your Microsoft account in **Settings → Accounts**. As in Prism Launcher, offline accounts can be added
   once an account that owns Minecraft is there, which is handy for testing multiplayer on one machine.
2. **Add Instance → Horizon**, pick a version and create the instance.
3. Launch it. The launcher downloads that Horizon release and prepares the game files from your own
   Minecraft: nothing from Minecraft is shipped with Horizon or this launcher.

Everything else (vanilla, modpacks, Modrinth, CurseForge) works as in Prism Launcher.

## What differs from Prism Launcher

- `launcher/horizon/`: the Horizon version list (GitHub releases of `horizon-rust/horizon`), its install
  and launch steps, and the **Horizon** page in **Add Instance**
- Releases are built by Prism's own workflow from this repository, and the launcher updates from them

The rest follows Prism Launcher's `release-11.x`; updates are rebased onto its new tags.

## Building

As for Prism Launcher: see its [build instructions](https://prismlauncher.org/wiki/development/build-instructions).

## Support

Problems with Horizon instances go to [this repository's issues](https://github.com/artemspt/PrismLauncher-Horizon/issues),
not to Prism Launcher's.

## License

All launcher code is available under the GPL-3.0-only license, as Prism Launcher's. The logo and related
assets are under the CC BY-SA 4.0 license.

Prism Launcher is by the [Prism Launcher contributors](https://github.com/PrismLauncher/PrismLauncher/graphs/contributors);
Horizon is by its [authors](https://github.com/horizon-rust/horizon).
