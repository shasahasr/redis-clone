## 2026-09-29
- Did: finished Step 0 (compiler, git, GitHub, project folder, first push) and Step 1 (terminal mini-Redis with SET/GET/DEL, case-insensitive commands, error handling, refactored into a Database class).
- Stuck on:
  - Blank line printed two errors. Fixed by skipping the command checks after the error (else / guard clause).
  - Ctrl+D caused an infinite loop. getline returns the stream, which is false on EOF, so break when it fails.
  - Created the istringstream before getline, so it copied an empty string. Streams copy the string when they're constructed.
  - Defined handle() as a free function. Member functions defined outside the class need Database::.
- Decisions: SET reads the rest of the line as the value, so values can have spaces. Real Redis needs quotes for this; RESP will handle it in Step 5.
- Next: Step 2, read Beej's guide ch. 1 to 5 and answer the four socket questions here.