open Jest;

open Expect;

let () =
  describe(
    "Clj.Array",
    () => {
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
      );
      describe(
        "rest",
        () => {
          test(
            "should return an array of all elements after the first",
            () => {
              expect([|1, 2|] |> Clj.Array.rest) |> toEqual(Some([|2|]));
              expect([|"a", "b", "c"|] |> Clj.Array.rest)
              |> toEqual(Some([|"b", "c"|]))
            }
          );
          test(
            "should return None for an array with one element",
            () => {
              expect([|1|] |> Clj.Array.rest) |> toEqual(None);
              expect([|"a"|] |> Clj.Array.rest) |> toEqual(None)
            }
          );
          test(
            "should return None for an empty array",
            () => expect([||] |> Clj.Array.rest) |> toEqual(None)
          )
        }
      );
      describe(
        "cons",
        () =>
          test(
            "should return a new array with an item at the front",
            {
              () => expect([||] |> Clj.Array.cons(1)) |> toEqual([|1|]);
              () =>
                expect([|"b"|] |> Clj.Array.cons("a")) |> toEqual([|"a", "b"|])
            }
          )
      )
    }
  );
