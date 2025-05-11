import mill._
import scalalib._
import $file.`rocket-chip`.dependencies.hardfloat.{common => hardfloatCommon}
import $file.`rocket-chip`.dependencies.cde.{common => cdeCommon}
import $file.`rocket-chip`.dependencies.diplomacy.{common => diplomacyCommon}
import $file.`rocket-chip`.{common => rocketChipCommon}

val chiselVersion = "7.0.0-M2"
val defaultScalaVersion = "2.13.14"
val pwd = os.Path(sys.env("MILL_WORKSPACE_ROOT"))

object v {
  def chiselIvy: Option[Dep] = Some(ivy"org.chipsalliance::chisel:${chiselVersion}")
  def chiselPluginIvy: Option[Dep] = Some(ivy"org.chipsalliance:::chisel-plugin:${chiselVersion}")
}

trait HasThisChisel extends SbtModule {
  def chiselModule: Option[ScalaModule] = None
  def chiselPluginJar: T[Option[PathRef]] = None
  def chiselIvy: Option[Dep] = v.chiselIvy
  def chiselPluginIvy: Option[Dep] = v.chiselPluginIvy
  override def scalaVersion = defaultScalaVersion
  override def scalacOptions = super.scalacOptions() ++
    Agg("-language:reflectiveCalls", "-Ymacro-annotations", "-Ytasty-reader")
  override def ivyDeps = super.ivyDeps() ++ Agg(chiselIvy.get)
  override def scalacPluginIvyDeps = super.scalacPluginIvyDeps() ++ Agg(chiselPluginIvy.get)
}

object rocketchip extends RocketChip
trait RocketChip extends rocketChipCommon.RocketChipModule with HasThisChisel {
  override def scalaVersion: T[String] = T(defaultScalaVersion)
  override def millSourcePath = pwd / "rocket-chip"
  def dependencyPath = pwd / "rocket-chip" / "dependencies"
  def macrosModule = macros
  def hardfloatModule = hardfloat
  def cdeModule = cde
  def diplomacyModule = diplomacy
  def diplomacyIvy = None
  def mainargsIvy = ivy"com.lihaoyi::mainargs:0.5.4"
  def json4sJacksonIvy = ivy"org.json4s::json4s-jackson:4.0.6"

  object macros extends Macros
  trait Macros extends rocketChipCommon.MacrosModule with SbtModule {
    def scalaVersion: T[String] = T(defaultScalaVersion)
    def scalaReflectIvy = ivy"org.scala-lang:scala-reflect:${defaultScalaVersion}"
  }

  object hardfloat extends Hardfloat
  trait Hardfloat extends hardfloatCommon.HardfloatModule with HasThisChisel {
    override def scalaVersion: T[String] = T(defaultScalaVersion)
    override def millSourcePath = dependencyPath / "hardfloat" / "hardfloat"
  }

  object cde extends CDE
  trait CDE extends cdeCommon.CDEModule with ScalaModule {
    def scalaVersion: T[String] = T(defaultScalaVersion)
    override def millSourcePath = dependencyPath / "cde" / "cde"
  }

  object diplomacy extends Diplomacy
  trait Diplomacy extends diplomacyCommon.DiplomacyModule with ScalaModule {
    def scalaVersion: T[String] = T(defaultScalaVersion)
    override def millSourcePath = dependencyPath / "diplomacy" / "diplomacy"

    def chiselModule: Option[ScalaModule] = None
    def chiselPluginJar: T[Option[PathRef]] = None
    def chiselIvy: Option[Dep] = v.chiselIvy
    def chiselPluginIvy: Option[Dep] = v.chiselPluginIvy

    def cdeModule = cde
    def sourcecodeIvy = ivy"com.lihaoyi::sourcecode:0.3.1"
  }
}

trait ysyxSoCModule extends ScalaModule {
  def rocketModule: ScalaModule
  override def moduleDeps = super.moduleDeps ++ Seq(
    rocketModule,
  )
}

object ysyxsoc extends ysyxSoC
trait ysyxSoC extends ysyxSoCModule with HasThisChisel {
  override def millSourcePath = pwd
  override def sources = Task.Sources(millSourcePath / "src")
  def rocketModule = rocketchip
}
