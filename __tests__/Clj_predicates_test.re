open Jest;

open Expect;

let () =
  describe(
    "Clj_predicates",
    () =>
      describe(
        "even",
        () => {
          test(
            "should return true if the integer is evenly divisible by 2",
            () => {
              expect(0 |> Clj_predicates.even) |> toEqual(true) |> ignore;
              expect(22 |> Clj_predicates.even) |> toEqual(true)
            }
          );
          test(
            "should return false if the integer is not evenly divisible by 2",
            () => {
              expect(1 |> Clj_predicates.even) |> toEqual(false) |> ignore;
              expect(37 |> Clj_predicates.even) |> toEqual(false)
            }
          )
        }
      )
  );
