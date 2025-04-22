# 📝 Commit Message Guide

Verwende diesen Leitfaden für konsistente Commit Messages mit Emojis, Issue-Verlinkung und klarer Struktur.

---

## 📌 Format

```text
<emoji> <type>(#issue): kurze Beschreibung in Kleinbuchstaben

Leere Zeile

Längere Erklärung im Body (optional)
```

### Beispiel

```text
🚀 feat(#1): add simple C++ Hello World program

Basic program that prints "Hello, World!" to the console using std::cout.
```

---

## 🧱 Commit-Typen & Beispiele

| Emoji | Type       | Beschreibung                                   | Beispiel Commit |
|-------|------------|------------------------------------------------|-----------------|
| 🚀    | `feat`     | Neues Feature oder neue Funktion               | `🚀 feat(#12): add login form with validation` |
| 🐛    | `fix`      | Bugfix oder Fehlerbehebung                     | `🐛 fix(#24): prevent crash when input is empty` |
| 🔄    | `refactor` | Code-Umstrukturierung ohne Funktionsänderung   | `🔄 refactor(#8): simplify loop logic in parser` |
| 🎨    | `style`    | Styling oder Formatierung (keine Logikänderung)| `🎨 style(#15): apply clang-format to all files` |
| 📚    | `docs`     | Dokumentation hinzufügen/ändern                | `📚 docs(#3): update README with setup instructions` |
| ✅    | `test`     | Tests hinzufügen oder anpassen                 | `✅ test(#5): add unit tests for utils.js` |
| 🔧    | `chore`    | Konfiguration, Wartung, Tooling                | `🔧 chore(#2): add .gitignore and editorconfig` |
| 🏗️    | `build`    | Build-System oder Abhängigkeiten               | `🏗️ build(#10): update g++ flags for debug build` |
| 👷    | `ci`       | CI/CD-Konfiguration                            | `👷 ci(#7): add GitHub Actions workflow for tests` |

---

## 🔗 Issue-Optionen

Verwende diese Optionen **nur im Scope** der Commit-Message (in den runden Klammern), um Issues zu verlinken:

| Option    | Beschreibung                                                                                       |
|-----------|----------------------------------------------------------------------------------------------------|
| **Closes**| Wird verwendet, um ein Issue nach dem Merge des Commits automatisch zu schließen. Beispiel: `Closes #42`. |
| **Fixes** | Verwendet, um ein Issue zu schließen, das durch den Commit behoben wird. Beispiel: `Fixes #13`.   |
| **Refs**  | Referenziert ein Issue, ohne es zu schließen. Beispiel: `Refs #7`. |
| **See**   | Wird verwendet, um auf ein Issue zu verweisen, ohne es zu schließen oder zu fixieren. Beispiel: `See #5`. |
| **Related** | Zeigt an, dass der Commit mit einem Issue in Verbindung steht, ohne dass es geschlossen oder behoben wird. Beispiel: `Related to #10`. |
