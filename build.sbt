import Dependencies._

lazy val root = (project in file(".")).
  settings(
    inThisBuild(List(
      organization := "runbikeswim",
      scalaVersion := "2.12.5",
      version      := "0.1.0-SNAPSHOT"
    )),
    name := "telephone-numbers-by-chess-moves",
    libraryDependencies += scalaTest % Test
  )
