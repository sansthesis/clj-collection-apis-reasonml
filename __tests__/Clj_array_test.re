open Jest;

open Expect;

let even = (a) => a mod 2 == 0;

let identity = (a) => a;

let () =
  describe(
    "Clj_array",
    () => {
      describe(
        "first",
        () => {
          test(
            "should retrieve the first element of a non-empty array",
            () => {
              expect([|1, 2|] |> Clj_array.first) |> toEqual(Some(1)) |> ignore;
              expect([|"a"|] |> Clj_array.first) |> toEqual(Some("a"))
            }
          );
          test(
            "should return None when given an empty array",
            () => expect([||] |> Clj_array.first) |> toEqual(None)
          )
        }
      );
      describe(
        "rest",
        () => {
          test(
            "should return an array of all elements after the first",
            () => {
              expect([|1, 2|] |> Clj_array.rest) |> toEqual([|2|]) |> ignore;
              expect([|"a", "b", "c"|] |> Clj_array.rest)
              |> toEqual([|"b", "c"|])
            }
          );
          test(
            "should return an empty array for an array with one element",
            () => {
              expect([|1|] |> Clj_array.rest) |> toEqual([||]) |> ignore;
              expect([|"a"|] |> Clj_array.rest) |> toEqual([||])
            }
          );
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.rest) |> toEqual([||])
          )
        }
      );
      describe(
        "next",
        () => {
          test(
            "should return an array of all elements after the first",
            () => {
              expect([|1, 2|] |> Clj_array.next)
              |> toEqual(Some([|2|]))
              |> ignore;
              expect([|"a", "b", "c"|] |> Clj_array.next)
              |> toEqual(Some([|"b", "c"|]))
            }
          );
          test(
            "should return None for an array with one element",
            () => {
              expect([|1|] |> Clj_array.next) |> toEqual(None) |> ignore;
              expect([|"a"|] |> Clj_array.next) |> toEqual(None)
            }
          );
          test(
            "should return None when given an empty array",
            () => expect([||] |> Clj_array.next) |> toEqual(None)
          )
        }
      );
      describe(
        "cons",
        () =>
          test(
            "should return a new array with an item at the front",
            () => {
              expect([||] |> Clj_array.cons(1)) |> toEqual([|1|]) |> ignore;
              expect([|"b"|] |> Clj_array.cons("a")) |> toEqual([|"a", "b"|])
            }
          )
      );
      describe(
        "filter",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.filter(even)) |> toEqual([||])
          );
          test(
            "should return an empty array when no elements match",
            () => expect([|1|] |> Clj_array.filter(even)) |> toEqual([||])
          );
          test(
            "should return an array with only elements that match",
            () => {
              expect([|2, 1, 3, 4|] |> Clj_array.filter(even))
              |> toEqual([|2, 4|])
              |> ignore;
              expect(
                [|"a", "b", "a", "c"|]
                |> Clj_array.filter((letter) => letter == "a")
              )
              |> toEqual([|"a", "a"|])
            }
          )
        }
      );
      describe(
        "distinct",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.distinct) |> toEqual([||])
          );
          test(
            "should return an array with no duplicate elements",
            () =>
              expect([|1, 2, 1, 1, 2, 3|] |> Clj_array.distinct)
              |> toEqual([|1, 2, 3|])
          )
        }
      );
      describe(
        "remove",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.remove(even)) |> toEqual([||])
          );
          test(
            "should return an empty array when no elements match",
            () => expect([|2|] |> Clj_array.remove(even)) |> toEqual([||])
          );
          test(
            "should return an array with only elements that don't match",
            () =>
              expect([|2, 1, 3, 4|] |> Clj_array.remove(even))
              |> toEqual([|1, 3|])
          )
        }
      );
      describe(
        "keep",
        () => {
          let contrived = (number) =>
            if (number mod 2 == 0) {
              Some(number + 10)
            } else {
              None
            };
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.keep(contrived)) |> toEqual([||])
          );
          test(
            "should remove all values that the fn returns None for",
            () =>
              expect([|1, 3, 5|] |> Clj_array.keep(contrived)) |> toEqual([||])
          );
          test(
            "should retain values that the fn returns Some(value) for",
            () =>
              expect([|2, 1, 4, 6, 3, 5, 8|] |> Clj_array.keep(contrived))
              |> toEqual([|12, 14, 16, 18|])
          )
        }
      );
      describe(
        "interpose",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.interpose(1)) |> toEqual([||])
          );
          test(
            "should insert the delimiter between elements",
            () =>
              expect([|0, 2|] |> Clj_array.interpose(1))
              |> toEqual([|0, 1, 2|])
          )
        }
      );
      describe(
        "drop",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.drop(1)) |> toEqual([||])
          );
          test(
            "should return an empty array when dropping more than it has",
            () => expect([|1|] |> Clj_array.drop(10)) |> toEqual([||])
          );
          test(
            "should remove the first N elements",
            () =>
              expect([|1, 2, 3, 4|] |> Clj_array.drop(2)) |> toEqual([|3, 4|])
          )
        }
      );
      describe(
        "dropWhile",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.dropWhile(even)) |> toEqual([||])
          );
          test(
            "should return the source array when the first result is false",
            () =>
              expect([|1, 2|] |> Clj_array.dropWhile(even))
              |> toEqual([|1, 2|])
          );
          test(
            "should return the suffix of array starting at the index of the first false result",
            () =>
              expect([|4, 2, 1, 2, 3|] |> Clj_array.dropWhile(even))
              |> toEqual([|1, 2, 3|])
          )
        }
      );
      describe(
        "take",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.take(10)) |> toEqual([||])
          );
          test(
            "should return the source array when taking more than it has",
            () => expect([|1|] |> Clj_array.take(10)) |> toEqual([|1|])
          );
          test(
            "should return the first N elements from the array",
            () =>
              expect([|1, 2, 3, 4|] |> Clj_array.take(2)) |> toEqual([|1, 2|])
          )
        }
      );
      describe(
        "takeNth",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.takeNth(2)) |> toEqual([||])
          );
          test(
            "should return the source array when N is 1",
            () =>
              expect([|1, 2, 3|] |> Clj_array.takeNth(1))
              |> toEqual([|1, 2, 3|])
          );
          test(
            "should return every Nth item in the array",
            () => {
              expect([|1, 2, 3, 4, 5, 6, 7|] |> Clj_array.takeNth(3))
              |> toEqual([|1, 4, 7|])
              |> ignore;
              expect([|1, 2, 3, 4, 5, 6|] |> Clj_array.takeNth(3))
              |> toEqual([|1, 4|])
            }
          )
        }
      );
      describe(
        "takeWhile",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.takeWhile(even)) |> toEqual([||])
          );
          test(
            "should return an empty array when the first element is false",
            () =>
              expect([|1, 2, 3|] |> Clj_array.takeWhile(even)) |> toEqual([||])
          );
          test(
            "should return the prefix of the array until the predicate is false",
            () =>
              expect([|2, 4, 6, 1, 2, 3, 4|] |> Clj_array.takeWhile(even))
              |> toEqual([|2, 4, 6|])
          )
        }
      );
      describe(
        "butLast",
        () => {
          test(
            "should return None when given an empty array",
            () => expect([||] |> Clj_array.butLast) |> toEqual(None)
          );
          test(
            "should return None when given an array with one element",
            () => expect([|1|] |> Clj_array.butLast) |> toEqual(None)
          );
          test(
            "should return an array of every element but the last in it",
            () =>
              expect([|1, 2, 3|] |> Clj_array.butLast)
              |> toEqual(Some([|1, 2|]))
          )
        }
      );
      describe(
        "dropLast",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.dropLast(5)) |> toEqual([||])
          );
          test(
            "should return an empty array when dropping more than the array has",
            () => expect([|1, 2|] |> Clj_array.dropLast(5)) |> toEqual([||])
          );
          test(
            "should return the source array when dropping 0",
            () =>
              expect([|1, 2|] |> Clj_array.dropLast(0)) |> toEqual([|1, 2|])
          );
          test(
            "should return an array of everything but the last N elements",
            () =>
              expect([|1, 2, 3, 4, 5|] |> Clj_array.dropLast(2))
              |> toEqual([|1, 2, 3|])
          )
        }
      );
      describe(
        "reverse",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.reverse) |> toEqual([||])
          );
          test(
            "should return the source array when given an array of 1 element",
            () => expect([|1|] |> Clj_array.reverse) |> toEqual([|1|])
          );
          test(
            "should return an array in reverse order of the original",
            () => {
              expect([|1, 2|] |> Clj_array.reverse)
              |> toEqual([|2, 1|])
              |> ignore;
              expect([|1, 2, 3, 4, 5|] |> Clj_array.reverse)
              |> toEqual([|5, 4, 3, 2, 1|])
            }
          )
        }
      );
      describe(
        "splitAt",
        () => {
          test(
            "should return an array of two empty arrays when given an empty array",
            () => {
              expect([||] |> Clj_array.splitAt(0))
              |> toEqual([|[||], [||]|])
              |> ignore;
              expect([||] |> Clj_array.splitAt(10)) |> toEqual([|[||], [||]|])
            }
          );
          test(
            "should put everything into the first array if splitting at a number higher than the array's length",
            () =>
              expect([|1, 2, 3|] |> Clj_array.splitAt(10))
              |> toEqual([|[|1, 2, 3|], [||]|])
          );
          test(
            "should put everything into the second array if splitting at 0",
            () =>
              expect([|1, 2, 3|] |> Clj_array.splitAt(0))
              |> toEqual([|[||], [|1, 2, 3|]|])
          );
          test(
            "should partition the array at the specified index",
            () => {
              expect([|1, 2, 3|] |> Clj_array.splitAt(1))
              |> toEqual([|[|1|], [|2, 3|]|])
              |> ignore;
              expect([|1, 2, 3|] |> Clj_array.splitAt(2))
              |> toEqual([|[|1, 2|], [|3|]|])
              |> ignore;
              expect([|1, 2, 3, 4|] |> Clj_array.splitAt(2))
              |> toEqual([|[|1, 2|], [|3, 4|]|])
            }
          )
        }
      );
      describe(
        "splitWith",
        () => {
          test(
            "should return an array of two empty arrays when given an empty array",
            () =>
              expect([||] |> Clj_array.splitWith(even))
              |> toEqual([|[||], [||]|])
          );
          test(
            "should put an array of one element into the second array if the predicate is false",
            () =>
              expect([|1|] |> Clj_array.splitWith(even))
              |> toEqual([|[||], [|1|]|])
          );
          test(
            "should put an array of one element into the first array if the predicate is true",
            () =>
              expect([|2|] |> Clj_array.splitWith(even))
              |> toEqual([|[|2|], [||]|])
          );
          test(
            "should split as much prefix where the predicate is true into the first array and the rest into the second array",
            () =>
              expect([|2, 1|] |> Clj_array.splitWith(even))
              |> toEqual([|[|2|], [|1|]|])
          )
        }
      );
      describe(
        "partition",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.partition(5)) |> toEqual([||])
          );
          test(
            "should return an empty array when partitioning by more than the array's size",
            () =>
              expect([|1, 2, 3|] |> Clj_array.partition(5)) |> toEqual([||])
          );
          test(
            "should return an array of arrays of single elements when partitioning by 1",
            () =>
              expect([|1, 2, 3|] |> Clj_array.partition(1))
              |> toEqual([|[|1|], [|2|], [|3|]|])
          );
          test(
            "should return an array of arrays of elements each of size N",
            () =>
              expect([|1, 2, 3, 4|] |> Clj_array.partition(2))
              |> toEqual([|[|1, 2|], [|3, 4|]|])
          );
          test(
            "should lose the items at the end that don't fill the last partition of size N",
            () =>
              expect([|1, 2, 3, 4|] |> Clj_array.partition(3))
              |> toEqual([|[|1, 2, 3|]|])
          )
        }
      );
      describe(
        "partitionAll",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.partitionAll(5)) |> toEqual([||])
          );
          test(
            "should return an array of an array of all elements in the source array when partitioning by more than the array's size",
            () =>
              expect([|1, 2, 3|] |> Clj_array.partitionAll(5))
              |> toEqual([|[|1, 2, 3|]|])
          );
          test(
            "should return an array of arrays of single elements when partitioning by 1",
            () =>
              expect([|1, 2, 3|] |> Clj_array.partitionAll(1))
              |> toEqual([|[|1|], [|2|], [|3|]|])
          );
          test(
            "should return an array of arrays of elements each of size N",
            () =>
              expect([|1, 2, 3, 4|] |> Clj_array.partitionAll(2))
              |> toEqual([|[|1, 2|], [|3, 4|]|])
          );
          test(
            "should include a smaller partition if the last items don't fill a partition of size N",
            () =>
              expect([|1, 2, 3, 4|] |> Clj_array.partitionAll(3))
              |> toEqual([|[|1, 2, 3|], [|4|]|])
          )
        }
      );
      describe(
        "partitionBy",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.partitionBy(even)) |> toEqual([||])
          );
          test(
            "should return an array of an array of a single element when given an array of one element",
            () =>
              expect([|1|] |> Clj_array.partitionBy(even))
              |> toEqual([|[|1|]|])
          );
          test(
            "should return an array of arrays of single elements when partitioning an array of ascending numbers by the identify function",
            () =>
              expect([|1, 2, 3|] |> Clj_array.partitionBy(identity))
              |> toEqual([|[|1|], [|2|], [|3|]|])
          );
          test(
            "should return an array of arrays of elements whenever the function value doesn't change",
            () =>
              expect(
                [|1, 2, 4, 6, 8, 1, 3, 2, 3|] |> Clj_array.partitionBy(even)
              )
              |> toEqual([|[|1|], [|2, 4, 6, 8|], [|1, 3|], [|2|], [|3|]|])
          )
        }
      );
      describe(
        "second",
        () => {
          test(
            "should return None when given an empty array",
            () => expect([||] |> Clj_array.second) |> toEqual(None)
          );
          test(
            "should return None for an array of one element",
            () => expect([|1|] |> Clj_array.second) |> toEqual(None)
          );
          test(
            "should return the second element in an array",
            () => expect([|1, 5|] |> Clj_array.second) |> toEqual(Some(5))
          )
        }
      );
      describe(
        "nth",
        () => {
          test(
            "should return the default value when given an empty array",
            () => expect([||] |> Clj_array.nth(0, 33)) |> toEqual(33)
          );
          test(
            "should return the default value when given an empty array",
            () => expect([||] |> Clj_array.nth(0, 33)) |> toEqual(33)
          );
          test(
            "should return the element at the specified index if it is within range",
            () => expect([|1, 2, 3|] |> Clj_array.nth(0, 33)) |> toEqual(1)
          )
        }
      );
      describe(
        "last",
        () => {
          test(
            "should return None when given an empty array",
            () => expect([||] |> Clj_array.last) |> toEqual(None)
          );
          test(
            "should return the final item in an array",
            () => {
              expect([|1|] |> Clj_array.last) |> toEqual(Some(1)) |> ignore;
              expect([|1, 2|] |> Clj_array.last) |> toEqual(Some(2))
            }
          )
        }
      );
      describe(
        "notEmpty",
        () => {
          test(
            "should return None when given an empty array",
            () => expect([||] |> Clj_array.notEmpty) |> toEqual(None)
          );
          test(
            "should return the source array for a non-empty array",
            () => {
              expect([|1|] |> Clj_array.notEmpty)
              |> toEqual(Some([|1|]))
              |> ignore;
              expect([|1, 2, 3|] |> Clj_array.notEmpty)
              |> toEqual(Some([|1, 2, 3|]))
            }
          )
        }
      );
      describe(
        "some",
        () => {
          test(
            "should return None when given an empty array",
            () => expect([||] |> Clj_array.some(even)) |> toEqual(None)
          );
          test(
            "should return None when the predicate returns true for no element in the array",
            () =>
              expect([|1, 3, 5, 7|] |> Clj_array.some(even)) |> toEqual(None)
          );
          test(
            "should return the first value in the array for which the predicate returns true",
            () =>
              expect([|1, 8, 3, 5, 7|] |> Clj_array.some(even))
              |> toEqual(Some(8))
          )
        }
      );
      describe(
        "every",
        () => {
          test(
            "should return true when given an empty array",
            () => expect([||] |> Clj_array.every(even)) |> toEqual(true)
          );
          test(
            "should return false when the predicate returns false for an element",
            () =>
              expect([|1, 2, 3|] |> Clj_array.every(even)) |> toEqual(false)
          );
          test(
            "should return true when the predicate returns true for all elements in the array",
            () =>
              expect([|2, 4, 6, 8, 0|] |> Clj_array.every(even))
              |> toEqual(true)
          )
        }
      );
      describe(
        "notEvery",
        () => {
          test(
            "should return false when given an empty array",
            () => expect([||] |> Clj_array.notEvery(even)) |> toEqual(false)
          );
          test(
            "should return true when the predicate returns false for an element",
            () =>
              expect([|1, 2, 3|] |> Clj_array.notEvery(even)) |> toEqual(true)
          );
          test(
            "should return false when the predicate returns true for all elements in the array",
            () =>
              expect([|2, 4, 6, 8, 0|] |> Clj_array.notEvery(even))
              |> toEqual(false)
          )
        }
      );
      describe(
        "notAny",
        () => {
          test(
            "should return true when given an empty array",
            () => expect([||] |> Clj_array.notAny(even)) |> toEqual(true)
          );
          test(
            "should return true when the predicate returns false for all elements in the array",
            () =>
              expect([|1, 3, 1, 5, 1, 1|] |> Clj_array.notAny(even))
              |> toEqual(true)
          );
          test(
            "should return false when the predicate returns true for an element",
            () =>
              expect([|1, 2, 3|] |> Clj_array.notAny(even)) |> toEqual(false)
          )
        }
      );
      describe(
        "empty",
        () => {
          test(
            "should return true when given an empty array",
            () => expect([||] |> Clj_array.empty) |> toEqual(true)
          );
          test(
            "should return false when given a non-empty array",
            () => expect([|1|] |> Clj_array.empty) |> toEqual(false)
          )
        }
      );
      describe(
        "repeatedly",
        () => {
          let dummy = () => 7;
          test(
            "should return an empty array when specified to call 0 times",
            () => expect(Clj_array.repeatedly(0, dummy)) |> toEqual([||])
          );
          test(
            "should return an array with one element when specified to call 1 time",
            () => expect(Clj_array.repeatedly(1, dummy)) |> toEqual([|7|])
          );
          test(
            "should return an array with N values from output of the invocation of the function called N times",
            () =>
              expect(Clj_array.repeatedly(5, dummy))
              |> toEqual([|7, 7, 7, 7, 7|])
          )
        }
      );
      describe(
        "repeat",
        () => {
          test(
            "should return an empty array when specified to call 0 times",
            () => expect(Clj_array.repeat(0, 1)) |> toEqual([||])
          );
          test(
            "should return an array with one element when specified to repeat 1 time",
            () => expect(Clj_array.repeat(1, 4)) |> toEqual([|4|])
          );
          test(
            "should return an array with N elements when specified to repeat N times",
            () => expect(Clj_array.repeat(3, 4)) |> toEqual([|4, 4, 4|])
          )
        }
      );
      describe(
        "range",
        () => {
          test(
            "should return an empty array when the start matches the end",
            () => expect(Clj_array.range(1, 1)) |> toEqual([||])
          );
          test(
            "should return an array of the start when the end is 1 higher than the start",
            () => expect(Clj_array.range(1, 2)) |> toEqual([|1|])
          );
          test(
            "should return an array from start to end - 1",
            () => expect(Clj_array.range(1, 5)) |> toEqual([|1, 2, 3, 4|])
          )
        }
      );
      describe(
        "dedupe",
        () => {
          test(
            "should return an empty array when given an empty array",
            () => expect([||] |> Clj_array.dedupe) |> toEqual([||])
          );
          test(
            "should return the source array when given an array without consecutive values",
            () =>
              expect([|1, 2, 3, 1|] |> Clj_array.dedupe)
              |> toEqual([|1, 2, 3, 1|])
          );
          test(
            "should return an array without consecutive duplicate values",
            () =>
              expect([|1, 1, 2, 2, 3, 1, 1|] |> Clj_array.dedupe)
              |> toEqual([|1, 2, 3, 1|])
          )
        }
      );
      describe(
        "conj",
        () => {
          test(
            "should return an array of one element when given None",
            () => expect(12 |> Clj_array.conj(None)) |> toEqual([|12|])
          );
          test(
            "should return an array of one element when given an empty array",
            () => expect(12 |> Clj_array.conj(Some([||]))) |> toEqual([|12|])
          );
          test(
            "should return add the item to the end of an existing array",
            () =>
              expect(12 |> Clj_array.conj(Some([|3, 4, 10|])))
              |> toEqual([|3, 4, 10, 12|])
          )
        }
      )
    }
  );
