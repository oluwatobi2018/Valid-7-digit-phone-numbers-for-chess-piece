package experiments

import org.scalatest.FunSuite

class TelephoneNumbersByChessMovesTest extends FunSuite {

  import TelephoneNumbersByChessMoves._
  import TelephoneNumbersByChessMoves.ChessPieces._

  /**
   * simple function for testing different telephone number lengths and starting positions
   */
  def getResultsAsString(func: (Array[List[Int]], Int) => Array[BigInt], piece: ChessPiece, minLength: Int, maxLength: Int): String = {

    val buffer = new StringBuffer()

    buffer.append(s"chess piece: ${piece}\n")
    for (l <- minLength to maxLength) {
      try {
        val r = func(successorsMap(piece), l)
        for (p <- 0 to 9) {
          buffer.append(f"start position: $p%2d, length: $l%3d, number of telephone-numbers: ${r(p)}%,34d\n")
        }
        buffer.append(f"\t  total number of telephone-numbers with length ${l}%4d: ${r.sum}%,34d\n\n")
      } catch {
        case e: Exception => buffer.append(f"error: ${e.toString()}%s\n")
      }
    }
    buffer.append((0 to 95).map(i => "*").mkString(""))
    buffer.toString
  }

  test("all moves of the king are valid for the queen") {
    for (position <- 0 to 9) {
      assert(successorsMap(King)(position).toSet.subsetOf(successorsMap(Queen)(position).toSet))
    }
  }

  test("all moves of the bishop and rook combined form the moves of the queen") {
    for (position <- 0 to 9) {
      assert((successorsMap(Bishop)(position).toSet ++ successorsMap(Rook)(position).toSet) == successorsMap(Queen)(position).toSet)
    }
  }

  test("queen and knight have only different successors") {
    for (position <- 0 to 9) {
      assert(successorsMap(Queen)(position).toSet.intersect(successorsMap(Knight)(position).toSet).isEmpty)
    }
  }

  test(s"results for the ${ChessPieces.Knight} and 10-digit numbers are correct") {
    val result = countTelephoneNumbers( successorsMap(ChessPieces.Knight), 10)
    assert(result.toList == List[BigInt](1760, 1424, 1424, 1424, 2304, 0, 2304, 1424, 1424, 1424))
  }
  
  test(s"results for the ${ChessPieces.Knight}") {
    println(getResultsAsString(countTelephoneNumbers, ChessPieces.Knight, 30, 31))
  }

  test(s"results for the ${ChessPieces.Bishop}") {
    println(getResultsAsString(countTelephoneNumbers, ChessPieces.Bishop, 30, 31))
  }

  test(s"results for the ${ChessPieces.Rook}") {
    println(getResultsAsString(countTelephoneNumbers, ChessPieces.Rook, 30, 31))
  }

  test(s"results for the ${ChessPieces.King}") {
    println(getResultsAsString(countTelephoneNumbers, ChessPieces.King, 30, 31))
  }

  test(s"results for the ${ChessPieces.Queen}") {
    println(getResultsAsString(countTelephoneNumbers, ChessPieces.Queen, 30, 31))
  }
}
