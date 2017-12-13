open Jest;

open Expect;

let () =
  describe(
    "hello",
    () => test("dummy let's force a line wrap", () => expect(1 + 2) |> toBe(3))
  );
