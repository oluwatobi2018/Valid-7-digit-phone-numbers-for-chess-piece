package experiments

import scala.annotation.tailrec

object TelephoneNumbersByChessMoves {

  object ChessPieces extends Enumeration {
    type ChessPiece = Value
    val Pawn, Knight, Bishop, Rook, Queen, King = Value
  }

  import ChessPieces._

  /**
   * successorsMap returns an array of possible successor-fields for each piece. The index in the array is the current position. 
   */
  val successorsMap = Map[ChessPiece, Array[List[Int]]](
    Pawn -> Array(Nil, List(4, 7), List(5, 8), List(6, 9), List(7), List(8), List(9), Nil, List(0), Nil),
    Knight -> Array(List(4, 6), List(6, 8), List(7, 9), List(4, 8), List(0, 3, 9), Nil, List(0, 1, 7), List(2, 6), List(1, 3), List(2, 4)),
    Bishop -> Array(List(7, 9), List(5, 9), List(4, 6), List(5, 7), List(2, 8), List(1, 3, 7, 9), List(2, 8), List(0, 3, 5), List(4, 6), List(0, 1, 5)),
    Rook -> Array(List(2, 5, 8), List(2, 3, 4, 7), List(0, 1, 3, 5, 8), List(1, 2, 6, 9), List(1, 5, 6, 7), List(0, 2, 4, 6, 8), List(3, 4, 5, 9), List(1, 4, 8, 9), List(0, 2, 5, 7, 9), List(3, 6, 7, 8)),
    Queen -> Array(List(2, 5, 7, 8, 9), List(2, 3, 4, 5, 7, 9), List(0, 1, 3, 4, 5, 6, 8), List(1, 2, 5, 6, 7, 9), List(1, 2, 5, 6, 7, 8), List(0, 1, 2, 3, 4, 6, 7, 8, 9), List(2, 3, 4, 5, 8, 9), List(0, 1, 3, 4, 5, 8, 9), List(0, 2, 4, 5, 6, 7, 9), List(0, 1, 3, 5, 6, 7, 8)),
    King -> Array(List(7, 8, 9), List(2, 4, 5), List(1, 3, 4, 5, 6), List(2, 5, 6), List(1, 2, 5, 7, 8), List(1, 2, 3, 4, 6, 7, 8, 9), List(2, 3, 5, 8, 9), List(0, 4, 5, 8), List(0, 4, 5, 6, 7, 9), List(0, 5, 6, 8)))

  /*
   * return an array with the number of telephone numbers for each possible starting position
   */
  def countTelephoneNumbers(successors: Array[List[Int]], numberLength: Int): Array[BigInt] = {

    val result = Array.ofDim[BigInt](2, 10) // stores results
    val currentIndex = (k: Int) => k % 2     // current index for array lengths
    val previousIndex = (k: Int) => 1 - (k % 2) // index of last iteration in array lengths, i.e. previous results

    @tailrec
    def countNumbersInner(length: Int, interation: Int): Unit =
      if (interation < length) {
        if (interation == 0) { // initialize lengths
          for (p <- 0 to 9) result(currentIndex(interation))(p) = BigInt(1)
        } else { // take previous results stored in lengths(1 - k % 2) to compute values for k and store that in lengths(k % 2)
          for (p <- 0 to 9) result(currentIndex(interation))(p) = successors(p).map(i => result(previousIndex(interation))(i)).sum
        }
        countNumbersInner(length, interation + 1)
      }

    if (numberLength < 0) {
      throw new IllegalArgumentException("This is bad!") // bogus input
    } else if (numberLength == 0) { // edge case of length 0, return a reasonable result nonetheless 
      (0 to 9).map(i => BigInt(1)).toArray // return that there exists 1 possibility (which is the empty string) for each position
    } else { // reasonable parameters
      countNumbersInner(numberLength, 0)
      result(previousIndex(numberLength))
    }
  }
}
