open Jest;

open Expect;

let even = (a) => a mod 2 == 0;

let identity = (a) => a;

let () =
  describe(
    "Clj_list",
    () => {
      describe(
        "first",
        () => {
          test(
            "should retrieve the first element of a non-empty list",
            () => {
              expect([1, 2] |> Clj_list.first) |> toEqual(Some(1)) |> ignore;
              expect(["a"] |> Clj_list.first) |> toEqual(Some("a"))
            }
          );
          test(
            "should return None when given an empty list",
            () => expect([] |> Clj_list.first) |> toEqual(None)
          )
        }
      );
      describe(
        "rest",
        () => {
          test(
            "should return an list of all elements after the first",
            () => {
              expect([1, 2] |> Clj_list.rest) |> toEqual([2]) |> ignore;
              expect(["a", "b", "c"] |> Clj_list.rest) |> toEqual(["b", "c"])
            }
          );
          test(
            "should return an empty list for an list with one element",
            () => {
              expect([1] |> Clj_list.rest) |> toEqual([]) |> ignore;
              expect(["a"] |> Clj_list.rest) |> toEqual([])
            }
          );
          test(
            "should return an empty list when given an empty list",
            () => expect([] |> Clj_list.rest) |> toEqual([])
          )
        }
      );
      describe(
        "next",
        () => {
          test(
            "should return an list of all elements after the first",
            () => {
              expect([1, 2] |> Clj_list.next) |> toEqual(Some([2])) |> ignore;
              expect(["a", "b", "c"] |> Clj_list.next)
              |> toEqual(Some(["b", "c"]))
            }
          );
          test(
            "should return None for an list with one element",
            () => {
              expect([1] |> Clj_list.next) |> toEqual(None) |> ignore;
              expect(["a"] |> Clj_list.next) |> toEqual(None)
            }
          );
          test(
            "should return None when given an empty list",
            () => expect([] |> Clj_list.next) |> toEqual(None)
          )
        }
      );
      describe(
        "cons",
        () =>
          test(
            "should return a new list with an item at the front",
            () => {
              expect([] |> Clj_list.cons(1)) |> toEqual([1]) |> ignore;
              expect(["b", "c"] |> Clj_list.cons("a"))
              |> toEqual(["a", "b", "c"])
            }
          )
      );
      describe(
        "distinct",
        () => {
          test(
            "should return an empty list when given an empty list",
            () => expect([] |> Clj_list.distinct) |> toEqual([])
          );
          test(
            "should return an list with no duplicate elements",
            () =>
              expect([1, 2, 1, 1, 2, 3] |> Clj_list.distinct)
              |> toEqual([1, 2, 3])
          )
        }
      );
      describe(
        "remove",
        () => {
          test(
            "should return an empty list when given an empty list",
            () => expect([] |> Clj_list.remove(even)) |> toEqual([])
          );
          test(
            "should return an empty list when no elements match",
            () => expect([2] |> Clj_list.remove(even)) |> toEqual([])
          );
          test(
            "should return an list with only elements that don't match",
            () =>
              expect([2, 1, 3, 4] |> Clj_list.remove(even)) |> toEqual([1, 3])
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
            "should return an empty list when given an empty list",
            () => expect([] |> Clj_list.keep(contrived)) |> toEqual([])
          );
          test(
            "should remove all values that the fn returns None for",
            () => expect([1, 3, 5] |> Clj_list.keep(contrived)) |> toEqual([])
          );
          test(
            "should retain values that the fn returns Some(value) for",
            () =>
              expect([2, 1, 4, 6, 3, 5, 8] |> Clj_list.keep(contrived))
              |> toEqual([12, 14, 16, 18])
          )
        }
      );
      describe(
        "interpose",
        () => {
          test(
            "should return an empty list when given an empty list",
            () => expect([] |> Clj_list.interpose(1)) |> toEqual([])
          );
          test(
            "should insert the delimiter between elements",
            () => {
              expect([0, 2] |> Clj_list.interpose(1))
              |> toEqual([0, 1, 2])
              |> ignore;
              expect([0, 2, 4] |> Clj_list.interpose(1))
              |> toEqual([0, 1, 2, 1, 4])
            }
          )
        }
      );
      describe(
        "drop",
        () => {
          test(
            "should return an empty list when given an empty list",
            () => expect([] |> Clj_list.drop(1)) |> toEqual([])
          );
          test(
            "should return an empty list when dropping more than it has",
            () => expect([1] |> Clj_list.drop(10)) |> toEqual([])
          );
          test(
            "should remove the first N elements",
            () => expect([1, 2, 3, 4] |> Clj_list.drop(2)) |> toEqual([3, 4])
          )
        }
      );
      describe(
        "dropWhile",
        () => {
          test(
            "should return an empty list when given an empty list",
            () => expect([] |> Clj_list.dropWhile(even)) |> toEqual([])
          );
          test(
            "should return the source list when the first result is false",
            () => expect([1, 2] |> Clj_list.dropWhile(even)) |> toEqual([1, 2])
          );
          test(
            "should return the suffix of list starting at the index of the first false result",
            () =>
              expect([4, 2, 1, 2, 3] |> Clj_list.dropWhile(even))
              |> toEqual([1, 2, 3])
          )
        }
      );
      describe(
        "take",
        () => {
          test(
            "should return an empty list when given an empty list",
            () => expect([] |> Clj_list.take(10)) |> toEqual([])
          );
          test(
            "should return the source list when taking more than it has",
            () => expect([1] |> Clj_list.take(10)) |> toEqual([1])
          );
          test(
            "should return the first N elements from the list",
            () => expect([1, 2, 3, 4] |> Clj_list.take(2)) |> toEqual([1, 2])
          )
        }
      );
      describe(
        "takeNth",
        () => {
          test(
            "should return an empty list when given an empty list",
            () => expect([] |> Clj_list.takeNth(2)) |> toEqual([])
          );
          test(
            "should return the source list when N is 1",
            () =>
              expect([1, 2, 3] |> Clj_list.takeNth(1)) |> toEqual([1, 2, 3])
          );
          test(
            "should return every Nth item in the list",
            () => {
              expect([1, 2, 3, 4, 5, 6, 7] |> Clj_list.takeNth(3))
              |> toEqual([1, 4, 7])
              |> ignore;
              expect([1, 2, 3, 4, 5, 6] |> Clj_list.takeNth(3))
              |> toEqual([1, 4])
            }
          )
        }
      );
      describe(
        "takeWhile",
        () => {
          test(
            "should return an empty list when given an empty list",
            () => expect([] |> Clj_list.takeWhile(even)) |> toEqual([])
          );
          test(
            "should return an empty list when the first element is false",
            () => expect([1, 2, 3] |> Clj_list.takeWhile(even)) |> toEqual([])
          );
          test(
            "should return the prefix of the list until the predicate is false",
            () =>
              expect([2, 4, 6, 1, 2, 3, 4] |> Clj_list.takeWhile(even))
              |> toEqual([2, 4, 6])
          )
        }
      );
      describe(
        "butLast",
        () => {
          test(
            "should return None when given an empty list",
            () => expect([] |> Clj_list.butLast) |> toEqual(None)
          );
          test(
            "should return None when given an list with one element",
            () => expect([1] |> Clj_list.butLast) |> toEqual(None)
          );
          test(
            "should return an list of every element but the last in it",
            () => {
              expect([1, 2, 3] |> Clj_list.butLast)
              |> toEqual(Some([1, 2]))
              |> ignore;
              expect([1, 2, 3, 4, 5] |> Clj_list.butLast)
              |> toEqual(Some([1, 2, 3, 4]))
            }
          )
        }
      );
      /*
       describe(
         "dropLast",
         () => {
           test(
             "should return an empty list when given an empty list",
             () => expect([] |> Clj_list.dropLast(5)) |> toEqual([])
           );
           test(
             "should return an empty list when dropping more than the list has",
             () => expect([1, 2] |> Clj_list.dropLast(5)) |> toEqual([])
           );
           test(
             "should return the source list when dropping 0",
             () => expect([1, 2] |> Clj_list.dropLast(0)) |> toEqual([1, 2])
           );
           test(
             "should return an list of everything but the last N elements",
             () =>
               expect([1, 2, 3, 4, 5] |> Clj_list.dropLast(2))
               |> toEqual([1, 2, 3])
           )
         }
       );
       */
      describe(
        "reverse",
        () => {
          test(
            "should return an empty list when given an empty list",
            () => expect([] |> Clj_list.reverse) |> toEqual([])
          );
          test(
            "should return the source list when given an list of 1 element",
            () => expect([1] |> Clj_list.reverse) |> toEqual([1])
          );
          test(
            "should return an list in reverse order of the original",
            () => {
              expect([1, 2] |> Clj_list.reverse) |> toEqual([2, 1]) |> ignore;
              expect([1, 2, 3, 4, 5] |> Clj_list.reverse)
              |> toEqual([5, 4, 3, 2, 1])
            }
          )
        }
      );
      describe(
        "splitAt",
        () => {
          test(
            "should return an list of two empty lists when given an empty list",
            () => {
              expect([] |> Clj_list.splitAt(0)) |> toEqual([[], []]) |> ignore;
              expect([] |> Clj_list.splitAt(10)) |> toEqual([[], []])
            }
          );
          test(
            "should put everything into the first list if splitting at a number higher than the list's length",
            () =>
              expect([1, 2, 3] |> Clj_list.splitAt(10))
              |> toEqual([[1, 2, 3], []])
          );
          test(
            "should put everything into the second list if splitting at 0",
            () =>
              expect([1, 2, 3] |> Clj_list.splitAt(0))
              |> toEqual([[], [1, 2, 3]])
          );
          test(
            "should partition the list at the specified index",
            () => {
              expect([1, 2, 3] |> Clj_list.splitAt(1))
              |> toEqual([[1], [2, 3]])
              |> ignore;
              expect([1, 2, 3] |> Clj_list.splitAt(2))
              |> toEqual([[1, 2], [3]])
              |> ignore;
              expect([1, 2, 3, 4] |> Clj_list.splitAt(2))
              |> toEqual([[1, 2], [3, 4]])
            }
          )
        }
      );
      describe(
        "splitWith",
        () => {
          test(
            "should return an list of two empty lists when given an empty list",
            () => expect([] |> Clj_list.splitWith(even)) |> toEqual([[], []])
          );
          test(
            "should put an list of one element into the second list if the predicate is false",
            () => expect([1] |> Clj_list.splitWith(even)) |> toEqual([[], [1]])
          );
          test(
            "should put an list of one element into the first list if the predicate is true",
            () => expect([2] |> Clj_list.splitWith(even)) |> toEqual([[2], []])
          );
          test(
            "should split as much prefix where the predicate is true into the first list and the rest into the second list",
            () =>
              expect([2, 1] |> Clj_list.splitWith(even)) |> toEqual([[2], [1]])
          )
        }
      )
      /*
       describe(
         "partition",
         () => {
           test(
             "should return an empty list when given an empty list",
             () => expect([] |> Clj_list.partition(5)) |> toEqual([])
           );
           test(
             "should return an empty list when partitioning by more than the list's size",
             () => expect([1, 2, 3] |> Clj_list.partition(5)) |> toEqual([])
           );
           test(
             "should return an list of lists of single elements when partitioning by 1",
             () =>
               expect([1, 2, 3] |> Clj_list.partition(1))
               |> toEqual([[1], [2], [3]])
           );
           test(
             "should return an list of lists of elements each of size N",
             () =>
               expect([1, 2, 3, 4] |> Clj_list.partition(2))
               |> toEqual([[1, 2], [3, 4]])
           );
           test(
             "should lose the items at the end that don't fill the last partition of size N",
             () =>
               expect([1, 2, 3, 4] |> Clj_list.partition(3))
               |> toEqual([[1, 2, 3]])
           )
         }
       );
       describe(
         "partitionAll",
         () => {
           test(
             "should return an empty list when given an empty list",
             () => expect([] |> Clj_list.partitionAll(5)) |> toEqual([])
           );
           test(
             "should return an list of an list of all elements in the source list when partitioning by more than the list's size",
             () =>
               expect([1, 2, 3] |> Clj_list.partitionAll(5))
               |> toEqual([[1, 2, 3]])
           );
           test(
             "should return an list of lists of single elements when partitioning by 1",
             () =>
               expect([1, 2, 3] |> Clj_list.partitionAll(1))
               |> toEqual([[1], [2], [3]])
           );
           test(
             "should return an list of lists of elements each of size N",
             () =>
               expect([1, 2, 3, 4] |> Clj_list.partitionAll(2))
               |> toEqual([[1, 2], [3, 4]])
           );
           test(
             "should include a smaller partition if the last items don't fill a partition of size N",
             () =>
               expect([1, 2, 3, 4] |> Clj_list.partitionAll(3))
               |> toEqual([[1, 2, 3], [4]])
           )
         }
       );
       describe(
         "partitionBy",
         () => {
           test(
             "should return an empty list when given an empty list",
             () => expect([] |> Clj_list.partitionBy(even)) |> toEqual([])
           );
           test(
             "should return an list of an list of a single element when given an list of one element",
             () => expect([1] |> Clj_list.partitionBy(even)) |> toEqual([[1]])
           );
           test(
             "should return an list of lists of single elements when partitioning an list of ascending numbers by the identify function",
             () =>
               expect([1, 2, 3] |> Clj_list.partitionBy(identity))
               |> toEqual([[1], [2], [3]])
           );
           test(
             "should return an list of lists of elements whenever the function value doesn't change",
             () =>
               expect([1, 2, 4, 6, 8, 1, 3, 2, 3] |> Clj_list.partitionBy(even))
               |> toEqual([[1], [2, 4, 6, 8], [1, 3], [2], [3]])
           )
         }
       );
       describe(
         "second",
         () => {
           test(
             "should return None when given an empty list",
             () => expect([] |> Clj_list.second) |> toEqual(None)
           );
           test(
             "should return None for an list of one element",
             () => expect([1] |> Clj_list.second) |> toEqual(None)
           );
           test(
             "should return the second element in an list",
             () => expect([1, 5] |> Clj_list.second) |> toEqual(Some(5))
           )
         }
       );
       describe(
         "nth",
         () => {
           test(
             "should return the default value when given an empty list",
             () => expect([] |> Clj_list.nth(0, 33)) |> toEqual(33)
           );
           test(
             "should return the default value when given an empty list",
             () => expect([] |> Clj_list.nth(0, 33)) |> toEqual(33)
           );
           test(
             "should return the element at the specified index if it is within range",
             () => expect([1, 2, 3] |> Clj_list.nth(0, 33)) |> toEqual(1)
           )
         }
       );
       describe(
         "last",
         () => {
           test(
             "should return None when given an empty list",
             () => expect([] |> Clj_list.last) |> toEqual(None)
           );
           test(
             "should return the final item in an list",
             () => {
               expect([1] |> Clj_list.last) |> toEqual(Some(1)) |> ignore;
               expect([1, 2] |> Clj_list.last) |> toEqual(Some(2))
             }
           )
         }
       );
       describe(
         "notEmpty",
         () => {
           test(
             "should return None when given an empty list",
             () => expect([] |> Clj_list.notEmpty) |> toEqual(None)
           );
           test(
             "should return the source list for a non-empty list",
             () => {
               expect([1] |> Clj_list.notEmpty) |> toEqual(Some([1])) |> ignore;
               expect([1, 2, 3] |> Clj_list.notEmpty)
               |> toEqual(Some([1, 2, 3]))
             }
           )
         }
       );
       describe(
         "some",
         () => {
           test(
             "should return None when given an empty list",
             () => expect([] |> Clj_list.some(even)) |> toEqual(None)
           );
           test(
             "should return None when the predicate returns true for no element in the list",
             () => expect([1, 3, 5, 7] |> Clj_list.some(even)) |> toEqual(None)
           );
           test(
             "should return the first value in the list for which the predicate returns true",
             () =>
               expect([1, 8, 3, 5, 7] |> Clj_list.some(even))
               |> toEqual(Some(8))
           )
         }
       );
       describe(
         "every",
         () => {
           test(
             "should return true when given an empty list",
             () => expect([] |> Clj_list.every(even)) |> toEqual(true)
           );
           test(
             "should return false when the predicate returns false for an element",
             () => expect([1, 2, 3] |> Clj_list.every(even)) |> toEqual(false)
           );
           test(
             "should return true when the predicate returns true for all elements in the list",
             () =>
               expect([2, 4, 6, 8, 0] |> Clj_list.every(even)) |> toEqual(true)
           )
         }
       );
       describe(
         "notEvery",
         () => {
           test(
             "should return false when given an empty list",
             () => expect([] |> Clj_list.notEvery(even)) |> toEqual(false)
           );
           test(
             "should return true when the predicate returns false for an element",
             () => expect([1, 2, 3] |> Clj_list.notEvery(even)) |> toEqual(true)
           );
           test(
             "should return false when the predicate returns true for all elements in the list",
             () =>
               expect([2, 4, 6, 8, 0] |> Clj_list.notEvery(even))
               |> toEqual(false)
           )
         }
       );
       describe(
         "notAny",
         () => {
           test(
             "should return true when given an empty list",
             () => expect([] |> Clj_list.notAny(even)) |> toEqual(true)
           );
           test(
             "should return true when the predicate returns false for all elements in the list",
             () =>
               expect([1, 3, 1, 5, 1, 1] |> Clj_list.notAny(even))
               |> toEqual(true)
           );
           test(
             "should return false when the predicate returns true for an element",
             () => expect([1, 2, 3] |> Clj_list.notAny(even)) |> toEqual(false)
           )
         }
       );
       describe(
         "empty",
         () => {
           test(
             "should return true when given an empty list",
             () => expect([] |> Clj_list.empty) |> toEqual(true)
           );
           test(
             "should return false when given a non-empty list",
             () => expect([1] |> Clj_list.empty) |> toEqual(false)
           )
         }
       );
       describe(
         "repeatedly",
         () => {
           let dummy = () => 7;
           test(
             "should return an empty list when specified to call 0 times",
             () => expect(Clj_list.repeatedly(0, dummy)) |> toEqual([])
           );
           test(
             "should return an list with one element when specified to call 1 time",
             () => expect(Clj_list.repeatedly(1, dummy)) |> toEqual([7])
           );
           test(
             "should return an list with N values from output of the invocation of the function called N times",
             () =>
               expect(Clj_list.repeatedly(5, dummy)) |> toEqual([7, 7, 7, 7, 7])
           )
         }
       );
       describe(
         "repeat",
         () => {
           test(
             "should return an empty list when specified to call 0 times",
             () => expect(Clj_list.repeat(0, 1)) |> toEqual([])
           );
           test(
             "should return an list with one element when specified to repeat 1 time",
             () => expect(Clj_list.repeat(1, 4)) |> toEqual([4])
           );
           test(
             "should return an list with N elements when specified to repeat N times",
             () => expect(Clj_list.repeat(3, 4)) |> toEqual([4, 4, 4])
           )
         }
       );
       describe(
         "range",
         () => {
           test(
             "should return an empty list when the start matches the end",
             () => expect(Clj_list.range(1, 1)) |> toEqual([])
           );
           test(
             "should return an list of the start when the end is 1 higher than the start",
             () => expect(Clj_list.range(1, 2)) |> toEqual([1])
           );
           test(
             "should return an list from start to end - 1",
             () => expect(Clj_list.range(1, 5)) |> toEqual([1, 2, 3, 4])
           )
         }
       );
       describe(
         "dedupe",
         () => {
           test(
             "should return an empty list when given an empty list",
             () => expect([] |> Clj_list.dedupe) |> toEqual([])
           );
           test(
             "should return the source list when given an list without consecutive values",
             () =>
               expect([1, 2, 3, 1] |> Clj_list.dedupe) |> toEqual([1, 2, 3, 1])
           );
           test(
             "should return an list without consecutive duplicate values",
             () =>
               expect([1, 1, 2, 2, 3, 1, 1] |> Clj_list.dedupe)
               |> toEqual([1, 2, 3, 1])
           )
         }
       );
       describe(
         "conj",
         () => {
           test(
             "should return an list of one element when given None",
             () => expect(12 |> Clj_list.conj(None)) |> toEqual([12])
           );
           test(
             "should return an list of one element when given an empty list",
             () => expect(12 |> Clj_list.conj(Some([]))) |> toEqual([12])
           );
           test(
             "should return add the item to the end of an existing list",
             () =>
               expect(12 |> Clj_list.conj(Some([3, 4, 10])))
               |> toEqual([3, 4, 10, 12])
           )
         }
       );
       describe(
         "contains",
         () => {
           test(
             "should return false when given an empty list",
             () => expect(Clj_list.contains([], 0)) |> toEqual(false)
           );
           test(
             "should return false when the given index is not within the list's bounds",
             () => expect(Clj_list.contains([1, 2, 3], 7)) |> toEqual(false)
           );
           test(
             "should return true when the given index is within the list's bounds",
             () => expect(Clj_list.contains([1, 2, 3], 1)) |> toEqual(true)
           )
         }
       )
       */
    }
  );
