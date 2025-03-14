package experiments

import scala.annotation.tailrec

object TelephoneNumbersByChessMoves {

  object ChessPieces extends Enumeration {
    type ChessPiece = Value
    val Pawn, Knight, Bishop, Rook, Queen, King = Value
  }

  import ChessPieces._

  val successorsMap: Map[ChessPiece, Array[List[Int]]] = Map(
    Pawn -> Array(Nil, List(4, 7), List(5, 8), List(6, 9), List(7), List(8), List(9), Nil, List(0), Nil),
    Knight -> Array(List(4, 6), List(6, 8), List(7, 9), List(4, 8), List(0, 3, 9), Nil, List(0, 1, 7), List(2, 6), List(1, 3), List(2, 4)),
    Bishop -> Array(List(7, 9), List(5, 9), List(4, 6), List(5, 7), List(2, 8), List(1, 3, 7, 9), List(2, 8), List(0, 3, 5), List(4, 6), List(0, 1, 5)),
    Rook -> Array(List(2, 5, 8), List(2, 3, 4, 7), List(0, 1, 3, 5, 8), List(1, 2, 6, 9), List(1, 5, 6, 7), List(0, 2, 4, 6, 8), List(3, 4, 5, 9), List(1, 4, 8, 9), List(0, 2, 5, 7, 9), List(3, 6, 7, 8)),
    Queen -> Array(List(2, 5, 7, 8, 9), List(2, 3, 4, 5, 7, 9), List(0, 1, 3, 4, 5, 6, 8), List(1, 2, 5, 6, 7, 9), List(1, 2, 5, 6, 7, 8), List(0, 1, 2, 3, 4, 6, 7, 8, 9), List(2, 3, 4, 5, 8, 9), List(0, 1, 3, 4, 5, 8, 9), List(0, 2, 4, 5, 6, 7, 9), List(0, 1, 3, 5, 6, 7, 8)),
    King -> Array(List(7, 8, 9), List(2, 4, 5), List(1, 3, 4, 5, 6), List(2, 5, 6), List(1, 2, 5, 7, 8), List(1, 2, 3, 4, 6, 7, 8, 9), List(2, 3, 5, 8, 9), List(0, 4, 5, 8), List(0, 4, 5, 6, 7, 9), List(0, 5, 6, 8))
  )

  def countTelephoneNumbers(successors: Array[List[Int]], numberLength: Int): Array[BigInt] = {
    require(numberLength >= 0, "Invalid input: numberLength cannot be negative.")

    if (numberLength == 0) return Array.fill(10)(BigInt(1))

    var prev = Array.fill(10)(BigInt(1))
    var curr = Array.fill(10)(BigInt(0))

    for (_ <- 1 until numberLength) {
      for (p <- 0 to 9) {
        curr(p) = successors(p).map(i => prev(i)).sum
      }
      val temp = prev
      prev = curr
      curr = temp
    }
    prev
  }
}
