# DOCX Practice Question Starters

These folders follow the three questions in `CSF213_Practice_Problems_CPP_v2`.
The DOCX is the source of the problem statements; the files here are starter
templates for practising the implementation and testing workflow.

Each question is independent and contains:

- a question-specific README;
- public headers that act like the supplied skeleton;
- incomplete `.cpp` files with TODOs;
- Mermaid UML and design notes;
- GoogleTest tests;
- an independent CMake project.

The starter tests are expected to fail before the TODOs are implemented. Keep
the class responsibilities from the question separate from the test code, and
use small TDD commits while solving.

| Folder | Question | Main focus |
| --- | --- | --- |
| `01_birthday_list` | Birthday List | cohesion, coupling, parallel collections, date queries |
| `02_birthday_list_person` | Birthday List Using a Person Class | encapsulation, aggregation, improved ownership |
| `03_book_cricket` | Book Cricket Simulator | enums, state, simulation, CRC/use cases, TDD |

Build one question at a time from its folder:

```text
cmake -S practice/docx_v2/01_birthday_list -B build-birthday-list
cmake --build build-birthday-list
ctest --test-dir build-birthday-list --output-on-failure
```

The Book Cricket model accepts page numbers through methods rather than hiding
randomness inside the domain classes. That keeps unit tests deterministic. A
random page generator can be added later in an application layer using the
standard library and `std::time(nullptr)` if desired; no `std::chrono` is used.
