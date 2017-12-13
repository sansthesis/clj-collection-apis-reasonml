open Jest;

open Expect;

let () =
  describe(
    "Clj.Array",
    () =>
      describe(
        "first",
        () => {
          test(
            "should retrieve the first element of a non-empty array",
            () => {
              expect([|1, 2|] |> Clj.Array.first) |> toEqual(Some(1));
              expect([|"a"|] |> Clj.Array.first) |> toEqual(Some("a"))
            }
          );
          test(
            "should return None for an empty array",
            () => expect([||] |> Clj.Array.first) |> toEqual(None)
          )
        }
      )
  );
