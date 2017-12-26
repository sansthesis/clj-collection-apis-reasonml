open Jest;

open Expect;

let () =
  describe(
    "Clj_predicates",
    () => {
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
      );
      describe(
        "odd",
        () => {
          test(
            "should return false if the integer is evenly divisible by 2",
            () => {
              expect(0 |> Clj_predicates.odd) |> toEqual(false) |> ignore;
              expect(22 |> Clj_predicates.odd) |> toEqual(false)
            }
          );
          test(
            "should return true if the integer is not evenly divisible by 2",
            () => {
              expect(1 |> Clj_predicates.odd) |> toEqual(true) |> ignore;
              expect(37 |> Clj_predicates.odd) |> toEqual(true)
            }
          )
        }
      );
      describe(
        "any",
        () =>
          test(
            "should return true no matter what the input is",
            () => {
              expect(0 |> Clj_predicates.any) |> toEqual(true) |> ignore;
              expect("hello there" |> Clj_predicates.any)
              |> toEqual(true)
              |> ignore;
              expect([|123, 456|] |> Clj_predicates.any)
              |> toEqual(true)
              |> ignore;
              expect(["abcd"] |> Clj_predicates.any) |> toEqual(true) |> ignore;
              expect(Some(11) |> Clj_predicates.any) |> toEqual(true) |> ignore;
              expect(false |> Clj_predicates.any) |> toEqual(true) |> ignore;
              expect((1, 2) |> Clj_predicates.any) |> toEqual(true) |> ignore;
              expect(None |> Clj_predicates.any) |> toEqual(true)
            }
          )
      );
      describe(
        "neg",
        () => {
          test(
            "should return true if the integer is less than zero",
            () => {
              expect((-1) |> Clj_predicates.neg) |> toEqual(true) |> ignore;
              expect((-401023) |> Clj_predicates.neg) |> toEqual(true)
            }
          );
          test(
            "should return false if the integer is greater than or equal to zero",
            () => {
              expect(0 |> Clj_predicates.neg) |> toEqual(false) |> ignore;
              expect(37 |> Clj_predicates.neg) |> toEqual(false)
            }
          )
        }
      );
      describe(
        "nil",
        () => {
          test(
            "should return true if the value is None",
            () => expect(None |> Clj_predicates.nil) |> toEqual(true)
          );
          test(
            "should return false if the value is not None",
            () => {
              expect(Some(None) |> Clj_predicates.nil)
              |> toEqual(false)
              |> ignore;
              expect(Some("hello") |> Clj_predicates.nil) |> toEqual(false)
            }
          )
        }
      );
      describe(
        "pos",
        () => {
          test(
            "should return true if the integer is greater than than zero",
            () => {
              expect(1 |> Clj_predicates.pos) |> toEqual(true) |> ignore;
              expect(401023 |> Clj_predicates.pos) |> toEqual(true)
            }
          );
          test(
            "should return false if the integer is less than or equal to zero",
            () => {
              expect(0 |> Clj_predicates.pos) |> toEqual(false) |> ignore;
              expect((-401) |> Clj_predicates.pos) |> toEqual(false)
            }
          )
        }
      );
      describe(
        "some",
        () => {
          test(
            "should return false if the value is None",
            () => expect(None |> Clj_predicates.some) |> toEqual(false)
          );
          test(
            "should return true if the value is not None",
            () => {
              expect(Some(None) |> Clj_predicates.some)
              |> toEqual(true)
              |> ignore;
              expect(Some("hello") |> Clj_predicates.some) |> toEqual(true)
            }
          )
        }
      )
    }
  );
