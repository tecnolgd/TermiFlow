### TermiFlow configuration file (`termiflow.conf`)

> The `termiflow.conf` file is the application's configuration file. It uses a simple INI-style structure with sections and `key=value` entries. The config controls runtime behavior and UI options; editing it changes how TermiFlow starts and behaves.

-  **Location**

    The file used by the app is located at `config/termiflow.conf` in the repository. When installed or packaged, the runtime looks for the same file path relative to the application.

- **Structure**

    - Sections: Denoted by square brackets, e.g. `[user_interface]`.
    - Keys: Each setting is `key=value`. Values are simple strings, booleans (`true`/`false`), or other literals depending on the setting.

- **What these mean**

    - `user_interface.theme`: Preferred theme. Typical values: `dark`, `light`, or a theme name supported by the app.
    - `user_interface.show_banner`: `true` to display the startup banner, `false` to hide it.
    - `behavior.auto_apply_theme`: If `true`, the app applies `user_interface.theme` automatically at startup.

- **Template / Suggested config**

    Copy this template to start with sensible defaults:
    ```ini
    [user_interface]
    theme=dark
    show_banner=true

    [behavior]
    auto_apply_theme=true
    ```

- **Editing note**

    - The file is plain text. Edit with any text editor and restart TermiFlow to apply changes.
    - Use `true` / `false` (lowercase) for boolean values.
    - Add new sections if the application supports them; consult source code that reads the config (`ConfigService`) for supported keys.