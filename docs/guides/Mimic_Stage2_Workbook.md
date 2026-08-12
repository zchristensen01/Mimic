# Mimic — Stage 2 Workbook

**Volume V · The Arm and ROS 2, session by session**

Fifteen sessions from two independent joints to a physical two-link planar arm you command in
Cartesian space. This is the stage that stretches — twelve weeks at hobby pace, eight at
yours — and print time, not your hours, is the constraint.

---

## Read this before you buy anything

**S2.4 contains a torque calculation that concludes your N20 motors cannot build this arm.** Not
"marginal" — short by **20× at the loaded shoulder** on an optimistic reading of the motor spec, and
by 100× on the manufacturer's own rated figure. S2.4 does that arithmetic and *What's Left to Buy*
Tier D1 carries the conclusion. S2.4 also shows that the
belt-reduction alternative, which looks cheaper, **does not close the gap** — including when you
stack it with shorter links, a counterbalance and base-mounted motors, which is the version most
people stop before checking.

Do S2.2 through S2.4 — geometry, kinematics, torque — **before** you buy a printer, choose motors, or
open CAD. They are three evenings of paper and they determine every mechanical decision that follows.
Getting the order wrong here is how people end up with a beautiful printed arm that sags.

---

## The gate you must have passed

Stage 1's exit criteria, all nine. Plus **native Ubuntu 24.04 installed and proven**, which is no
longer optional: `socketCAN` does not exist in a stock WSL2 kernel, Gazebo Harmonic's rendering
through WSLg is inconsistent, and ROS 2's DDS discovery across the WSL network boundary produces
nodes that cannot see each other. Debugging that while also debugging your own robot is the
two-fronts problem in its purest form.

---

## The standing rule, and the form it takes in this stage

**Capture the broken state before you fix it.** Each session's *What will go wrong* ends by naming
the one worth catching.

In Stage 2 that is almost always **a screenshot**, because this is the stage where the failures
happen on a screen rather than on a bench. Take it as a still rather than a video: a still of
readable text beats a recording of the same text every time, because a reader can stop on it, and
because `ros2 control list_hardware_interfaces` with an unclaimed command interface in it is a
*document* rather than a moment.

Three of this stage's failures are worth being greedy about, because they are famous and instantly
recognisable to anyone who has used this stack:

- **rviz2 rendering an empty scene** because Fixed Frame is still `map`.
- **An arm exploding on spawn** in Gazebo from a bad inertia tensor.
- **MoveIt reporting a successful plan** while the hardware sits motionless.

Someone who has debugged ROS 2 sees any of those and knows immediately that you were in the same
place they were. That recognition is worth more than a clean screenshot of the same tool working,
which every tutorial already has.

And the printed failures are physical: **keep the parts.** The coupon whose bearing seat came out
undersized and the link that snapped along its layer lines are better photographs than either of
their successors, and they cost nothing to keep in a box.

---

# PART I — PAPER

---

## S2.0 · The host, proven

**Goal:** Ubuntu 24.04, ROS 2 Jazzy, Gazebo Harmonic, and socketCAN, all verified in one evening so
you never wonder about them again.

**You will be able to:** state which parts of this stack cannot run under WSL and why — as a property of the kernel and the graphics path rather than as a rule you were given — and prove each of the four works on a machine you set up.

### Build

Install order matters:

1. **Ubuntu 24.04 LTS**, native — dual-boot, dedicated SSD, or the laptop. Back up first.
2. **ROS 2 Jazzy Jalisco**, desktop variant, following the current instructions at `docs.ros.org`.
   **Do not follow a third-party blog.** The official apt setup changes periodically and stale
   instructions are the most common reason an install fails confusingly.
3. **Gazebo Harmonic** — the simulator paired with Jazzy.
4. `python3-colcon-common-extensions`, `python3-rosdep`, `python3-vcstool`
5. `can-utils` — `candump` and `cansend`. This is the software that does not exist in WSL and the
   practical reason this machine has to be real.
6. `sudo usermod -aG dialout $USER`, then log out and back in.

**Open a host-setup ADR in `docs/decisions/` and finish it the same evening**, with the date on it.
Which machine, and why that one — dual-boot, spare SSD or the laptop — plus what you gave up to get
it. The date is the load-bearing part: it is the moment Stage 2 stopped being blocked on
infrastructure, and it is the kind of thing that is obvious now and unreconstructable later.

### Prove it — four checks, once, then never again

```bash
# 1. Two nodes can find each other
ros2 run demo_nodes_cpp talker        # ... and in a second terminal:
ros2 run demo_nodes_py listener

# 2. The visualiser renders
rviz2

# 3. The simulator renders — note 'gz sim', NOT 'gazebo'
gz sim shapes.sdf

# 4. socketCAN, on a virtual bus, no hardware needed
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
candump vcan0 &
cansend vcan0 001#1122334455667788
```

> **WATCH OUT** — **Gazebo Classic is end-of-life and unsupported from Jazzy onward.** Any tutorial using
> it is stale and following one will cost you a weekend. The tell is in the names: Classic is
> `gazebo` and `gazebo_ros`; Harmonic is `gz sim` and `ros_gz`. Check the command names before
> committing an afternoon to any tutorial, including ones that look current.

### Draw this

**Nothing. This is an install, not a design.** The one page worth producing is a note in
the host-setup ADR recording what broke and what fixed it, and that is prose because the answer is
a package name or a missing group membership rather than a shape.

### What will go wrong

- **`apt` cannot find the ROS 2 packages.** The apt source or the key was added wrong, or you followed
  a blog whose instructions predate the current setup. Go back to `docs.ros.org` and do it their way;
  this changes periodically and it is the single most common reason an install fails confusingly.
- **`ros2` is not a command in a new terminal.** You have not sourced `/opt/ros/jazzy/setup.bash`.
  Everyone hits this once. Adding it to `.bashrc` is the usual fix and is fine for one distribution on
  one machine — just know that is what you did.
- **talker and listener both run and neither sees the other.** Firewall, or two different `ROS_DOMAIN_ID`
  values, or you are half in WSL and half native. Check `ros2 node list` from a third terminal.
- **`gz sim` opens a black window.** No GPU acceleration. On native hardware this is a driver
  problem; if you are seeing it under WSL, that is the thing this session exists to make you stop
  doing.
- **`cansend` says "Network is down".** You created `vcan0` but did not bring it up — `ip link set up
  vcan0` is a separate command from `ip link add`.
- **`candump` prints nothing and no error.** It is running in the background from the `&` and its
  output went to a terminal you have since scrolled. Run it in its own terminal for this test.

> **CHECK YOURSELF** — Check 4 is the one that cannot pass in WSL. Say **why**, in one sentence, and
> make it a sentence about the kernel rather than about a rule you were given. Then answer the second
> half: checks 2 and 3 *can* run under WSL and are still on this list. What are they here to catch that
> WSL would have hidden?

**Capture the broken state.** Nothing. This session's `Site:` line is `nothing` and it applies here
too — an install that went wrong and then went right is not evidence of anything except that
installs are like that. The one thing worth keeping is not a photograph: note in
the host-setup ADR what actually broke and what fixed it, because you will install this stack
again on another machine one day and that note will save you the evening.

### Artifacts

- **`docs/sessions/ros2-host/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- The host-setup ADR in `docs/decisions/`, with the date. It is the moment Stage 2 stopped being blocked
  on infrastructure.
- **Site:** nothing. This session produces no artifact worth showing and that is correct — infrastructure
  is the price of the work, not the work. Noted explicitly so its absence reads as a decision rather
  than an omission.
  **The shot:** nothing.

---

## S2.1 · ROS 2, the graph — and a stop condition

**Goal:** fluency with nodes, topics, services, actions, parameters, and launch files. Nothing about
your robot yet.

**You will be able to:** take a running ROS 2 system you did not write and work out from the command line alone what it is doing; and say when a topic, a service and an action are each the right choice rather than reciting the difference.

### Concept

ROS 2 is not a library you import. It is a set of conventions about how robot software is
decomposed — separate processes, discovering each other at runtime, passing typed messages. Learning
it is mostly learning the conventions.

Analogy: it is closer to HTTP and a service mesh than to a framework. Nobody "learns HTTP" by reading
the library — you learn that requests have verbs, that responses have status codes, and that anyone
speaking the protocol can join. ROS 2 is the same shape: nodes are processes, topics are the
publish/subscribe channel, and the useful knowledge is the conventions rather than the API. You have
built distributed systems before; this is one, with a message bus and a discovery mechanism, and
almost everything that confuses beginners here is something you already know under another name.

### The stop condition

Work the official `docs.ros.org` Jazzy tutorials — the beginner CLI and client-library sets. **Stop
when you can do these five things without looking anything up**, and not later:

1. Write a publisher and a subscriber in Python, and the same pair in C++.
2. Explain the difference between a topic, a service, and an action, and say when each is correct.
3. Write a launch file that starts three nodes with parameters from a YAML file.
4. Use `ros2 topic echo`, `ros2 node info`, `ros2 param get`, and `rqt_graph` to inspect a running
   system you did not write.
5. Explain what colcon does and why `source install/setup.bash` is necessary.

> **WATCH OUT** — The guide's warning applies in reverse here. Reading ROS 2 tutorials *during Stage 0*
> was procrastination. Reading them *now* is the work — but there is no end to them, and the failure
> mode at this stage is tutorial drift: four weeks of exercises that never touch your arm. Five
> criteria above. Meet them and move on.

### The five words that cause the most confusion

Learn these first; almost every early ROS 2 problem is one of them misunderstood.

> **DEFINITION** — **Workspace, overlay, and `source install/setup.bash`.** A **workspace** is a directory
> with a `src/` folder full of packages, which `colcon build` compiles into `build/`, `install/` and
> `log/`. Sourcing `install/setup.bash` prepends that workspace to the environment variables ROS 2
> uses to find packages — so your version of a package **overlays** the system one from
> `/opt/ros/jazzy`. Two consequences follow, and both bite everyone once. First, a new terminal knows
> nothing until you source; "my node disappeared" is almost always a fresh terminal. Second, sourcing
> a workspace whose build is stale gives you *old code running under a new name*, which is far more
> confusing than a build error. When something makes no sense, `rm -rf build install log` and rebuild
> before you debug anything.

> **DEFINITION** — **Launch file.** A Python (or XML/YAML) script that starts a set of nodes with their
> parameters, remappings and conditions, so that bringing up a robot is one command instead of six
> terminals. It is ordinary code — you can compute values, read arguments, and branch — which is both
> its strength and the reason launch files quietly become the least readable part of a ROS 2 project.
> Write yours once, with arguments, rather than three near-copies.

> **DEFINITION** — **QoS — quality of service.** DDS lets each publisher and subscriber declare how
> delivery should behave: *reliability* (retry until delivered, or fire and forget), *durability*
> (should a late subscriber receive the last message, or only new ones), *history* and *depth*. This
> matters because **a publisher and a subscriber whose QoS profiles are incompatible simply do not
> connect** — no error, no warning, just a topic with a publisher and a subscriber and no messages.
> `ros2 topic info -v` shows both profiles and is the tool that diagnoses it. The usual cases: sensor
> data is *best effort*, and `/robot_description` is *transient local* so that a node started later
> still receives it.

> **LOOK THIS UP** — The official `docs.ros.org` Jazzy tutorials are the right primary source and you
> should work them. Alongside them, **Articulated Robotics** (Josh Newans) is the best video series for
> this specific project shape — a small differential or articulated robot built up from URDF through
> `ros2_control` — and his ordering matches this workbook's closely enough to use as a second pass. Use
> the official docs to learn the API and the video series to see the workflow.

### What order to work them in, because fifteen hours needs a shape

This is the longest session in the project and the only one where the material is somebody else's
tutorials. Left unstructured it becomes four weeks. A shape that works, roughly three hours a block:

| Block | Work | Stop condition |
|---|---|---|
| 1 | CLI tools: `ros2 node`, `topic`, `service`, `param`, and `rqt_graph`, against the demo nodes | You can inspect a running system you did not write |
| 2 | Write a publisher and a subscriber in **Python** | Yours talks to the demo nodes and back |
| 3 | The same pair in **C++**, plus `colcon build` and what `install/setup.bash` does | You can explain why a new terminal knows nothing |
| 4 | Services and actions — write one of each, small | You can say when each is correct rather than reciting the difference |
| 5 | Launch files and parameters from YAML | One command starts three nodes with their parameters |

**Do not do the tf2 or URDF tutorials here.** They arrive in S2.6 with a robot to describe, and doing
them now means learning them twice.

### Draw this

**One, and it is already in *Prove it* below** — the node graph of `demo_nodes_cpp`, drawn by hand
from the command line alone and then checked against `rqt_graph`. That is the drawing for this
session and it is deliberately placed as a test rather than as an exercise, because drawing a graph
you have been shown teaches nothing and reconstructing one you have only inspected teaches the
skill the whole session is for.

### What will go wrong

- **Your package builds and `ros2 run` cannot find it.** You did not source the workspace, or you
  sourced it in a different terminal, or the build is stale. `rm -rf build install log` and rebuild
  before you debug anything.
- **A publisher and a subscriber both exist on the same topic and no messages arrive.** Incompatible
  QoS. `ros2 topic info -v` shows both profiles side by side and is the only tool that diagnoses this.
- **`colcon build` succeeds and your changes have no effect.** You have two copies of the package —
  one in the workspace and one installed from apt — and the overlay is picking the wrong one, or your
  Python package is installed rather than symlinked. `--symlink-install` while you are iterating.
- **Everything works and you cannot stop.** The real failure mode of this session. The five criteria
  above are the exit gate; meet them and go and do kinematics.

**Capture the broken state.** Nothing, deliberately. This session's `Site:` line is `nothing` for
the same reason: tutorial exercises are not portfolio material, and a screenshot of a QoS
mismatch you hit while working through somebody else's examples is a screenshot of the tutorial. The
capture discipline resumes at S2.2, where the work becomes yours.

### Prove it

Do not leave this session on a feeling. Take a package you did not write — `demo_nodes_cpp` is
fine — and, without reading its source, work out from the command line alone: what nodes it starts,
what topics they publish and subscribe, what the message type on each is, and what parameters each
node exposes. Then draw the node graph by hand and check it against `rqt_graph`.

That exercise is the actual skill this session buys. Every hour after this one is spent inspecting a
running system you only partly understand, and doing it deliberately once is what turns fifteen hours
of tutorials into something you keep.

> **CHECK YOURSELF** — Answer the five stop conditions honestly, out loud, without opening anything. If
> you have to look up how to write a subscriber, you are not finished. If you can write one but cannot
> say why a service would have been wrong for it, you are also not finished — and that second one is
> the answer people skip.

### Artifacts

- **`docs/sessions/ros2-fundamentals/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- A small `mimic_ros2_scratch` package with your publisher/subscriber pair in both languages, your
  service, your action and your launch file. It is throwaway code and committing it is still worth it —
  it is dated evidence of the week you learned this, and you will copy from it in S2.6.
- The hand-drawn node graph of `demo_nodes_cpp`, photographed, beside the `rqt_graph` output.
- **Site:** nothing, deliberately. Tutorials are not portfolio material, and a stage that shows its
  tutorial exercises reads as a course followed rather than a machine built. The next twelve sessions
  are where the site content lives.
  **The shot:** nothing.

---

## S2.2 · Forward kinematics, derived

**Goal:** given two joint angles, you can compute where the gripper tip is — on paper, then in Python,
and the two agree.

**You will be able to:** derive forward kinematics for a two-link arm by walking the chain, without looking it up; and state your arm's reachable workspace as two radii, explaining where each one comes from.

### Concept

An arm is a chain of coordinate frames, each defined relative to the one before it. Forward
kinematics asks: given the angles, where is the end? It always has exactly one answer, and for a
two-link planar arm it is two lines of trigonometry.

This geometry was chosen precisely because you can do it by hand. Every larger arm forces you to
import a solver and trust it.

### The math — derive it, do not copy it

Frames: `base_link` at the shoulder pivot, `θ1` from the +x axis, `θ2` measured **relative to link 1**
(this is a choice — the alternative is absolute, and mixing them is a classic error).

```
FIGURE S2.2.1 — The geometry everything in Stage 2 refers back to

                                              ● gripper_tip
                                            ╱   (x, y)
                                          ╱
                                    L₂  ╱
                                      ╱
                                    ╱ ) θ₂   ← RELATIVE to link 1
                        elbow  ●──╱──────────  (dashed = link 1 extended)
                             ╱
                           ╱
                     L₁  ╱
                       ╱
                     ╱ ) θ₁          ← ABSOLUTE, from +x
   base_link  ●────────────────────────────────► +x
   (shoulder)

   x = L₁·cos θ₁ + L₂·cos(θ₁ + θ₂)      the (θ₁+θ₂) is the whole
   y = L₁·sin θ₁ + L₂·sin(θ₁ + θ₂)      content of the derivation

   WORKSPACE, L₁ = L₂ = L = 180 mm

   For equal links the reach collapses to one clean formula. Derive it
   from the law of cosines and you get:

              r = 2L · cos(θ₂ / 2)

   ASSUME FOR NOW: 15° ≤ θ₂ ≤ 165°. You derive that limit in S2.3, one
   session later, from det J = L₁L₂ sin θ₂ going to zero at θ₂ = 0 and
   θ₂ = π — full extension and full fold, where the arm is singular and
   some tip directions need infinite joint speed. 15° is a chosen stand-
   off from each, not a derived constant. Take it on credit here; the
   next session is where it is earned.

   That limit maps DIRECTLY onto two radii:

     θ₂ =  15°  →  r = 360 · cos(7.5°)  = 356.9 mm   outer bound
     θ₂ = 165°  →  r = 360 · cos(82.5°) =  47.0 mm   inner bound

              ╭─────────────────────╮
            ╱                         ╲
          │                             │
          │           ╭───╮             │
          │           │ ✗ │             │   ← 47 mm unreachable disc
          │           ╰───╯             │      in the CENTRE. 94 mm
          │        r = 47 mm            │      across, and it decides
            ╲                         ╱        your bench layout.
              ╰─────────────────────╯
                 outer boundary r = 356.9 mm

   The 3.1 mm rim outside that boundary — 360 − 356.9, lost to the same
   elbow limit — is 0.9 % of the radius and is deliberately NOT drawn.
   At this scale it would come out as thick as the 47 mm hole, which is
   15× larger, and you would conclude the outer loss matters. It does
   not. It is in the arithmetic above and nowhere else.

   REACHABLE:  47.0 mm  ≤  r  ≤  356.9 mm      an annulus, not a disc

   Equal links remove the hole that |L₁ − L₂| would create — but the
   elbow limit puts a DIFFERENT hole back, and it is the bigger of the
   two. Anything you want to pick up must sit outside a 94 mm circle
   centred on the shoulder. That is a bench-layout constraint, and it
   is why S2.5 keeps the arm's own base out of its own workspace.
```

```
Elbow position:
  x₁ = L₁·cos θ₁
  y₁ = L₁·sin θ₁

Tip position:
  x = L₁·cos θ₁ + L₂·cos(θ₁ + θ₂)
  y = L₁·sin θ₁ + L₂·sin(θ₁ + θ₂)
```

Derive it by walking the chain: get to the elbow, rotate by θ₂ *on top of* θ₁, walk L₂ further. The
`(θ₁ + θ₂)` is the whole content of the derivation and it is why the relative-angle convention is
worth choosing.

**The workspace, and the hole nobody expects.** With `L₁ ≠ L₂` the reachable set is obviously an
annulus: outer radius `L₁ + L₂`, inner radius `|L₁ − L₂|`. Equal links make that inner radius zero,
which is the usual reason to choose them — and it is *not* the end of the story, because the elbow
limit puts a larger hole back.

> **WATCH OUT** — **This section uses a number you have not derived yet, and it is the one forward
> reference in Stage 2.** The elbow limit `15° ≤ θ₂ ≤ 165°` comes out of S2.3's Jacobian: `det J =
> L₁L₂ sin θ₂` is zero at θ₂ = 0 and θ₂ = π, so those two poses are singular and you design them out
> rather than meeting them at speed. The 15° stand-off itself is a *choice* — far enough from the
> singularity that the Jacobian is comfortably invertible, close enough that you keep almost all your
> reach — and S2.3 is where you make it. Assume it here, and if S2.3 leads you to a different
> stand-off, come back and re-run the two radii below; they are one `cos` each.

**Derive it, and here is the route rather than the answer.** Two ways in, and doing it both ways once
is worth the twenty minutes because they check each other:

- **The algebraic route.** Take your two FK equations, square both, and add them. Everything with a
  single θ collapses through `sin² + cos² = 1`, and the cross terms collapse through the angle-
  difference identity for cosine. What survives is a single expression in θ₂ alone — which is itself
  the interesting result, because it says the *distance* to the tip does not depend on where the
  shoulder is pointing. Get there yourself before you look at the next line.
- **The geometric route.** Shoulder, elbow and tip form a triangle with sides `L₁`, `L₂` and `r`, and
  the angle at the elbow between the two links is `π − θ₂`. Write the law of cosines for that
  triangle and simplify.

Both give `r² = 2L²(1 + cos θ₂)` for equal links, and the half-angle identity `1 + cos θ = 2cos²(θ/2)`
collapses that to:

```
r = 2L · cos(θ₂ / 2)
```

which is worth deriving once because it makes the whole workspace a single monotonic function of one
angle. Substituting your limits at `L = 180 mm`:

```
θ₂ =  15°  →  r = 356.9 mm     you lose a 3.1 mm rim at the outside
θ₂ = 165°  →  r =  47.0 mm     you lose a 47 mm disc at the centre
```

**Your reachable workspace is the annulus 47.0 mm ≤ r ≤ 356.9 mm.** The outer loss is negligible. The
inner one is not: it is a 94 mm circle centred on the shoulder that the tip can never enter, and it
is a constraint on where you put objects on the bench in Stage 3. Write both numbers into
`docs/decisions/` next to the elbow limit — they are the same decision expressed in Cartesian space,
and this is the form you will actually use.

> **DEFINITION** — **Annulus.** The region between two concentric circles — a disc with a smaller disc
> removed from its middle. It is the natural shape of a planar arm's workspace, and the word is worth
> having because "the reachable annulus" is a great deal more precise than "the area it can get to."

> **DEFINITION** — **Revolute and prismatic joints.** A **revolute** joint rotates about an axis; a
> **prismatic** joint slides along one. Both are one degree of freedom, and between them they cover
> almost everything you will describe in URDF. Your shoulder and elbow are revolute. A parallel-jaw
> gripper is usually modelled as prismatic, because the jaw translates even though a servo rotates —
> URDF describes the *motion*, not the mechanism that produces it. There is also `fixed` (zero degrees
> of freedom, used for rigidly attached frames like `gripper_tip`) and `continuous`, which is revolute
> without limits.

> **DEFINITION** — **Homogeneous transform.** A rotation and a translation packed into one 4×4 matrix, so
> that composing transforms is matrix multiplication and inverting one is a matrix inverse. Your
> two-line FK above *is* the product of two such matrices, expanded. Write it both ways once — as
> trigonometry and as a matrix product — and confirm they give the same answer. That is the moment
> the linear algebra on your skills list stops being vocabulary.

### Draw this

The arm, twice, on one page — and use **your** angle conventions, not the figure's.

**First, the configuration.** Draw the two links at some arbitrary non-trivial pose. Mark the +x axis,
mark θ₁ from it, and mark θ₂ *from the extension of link 1* with the dashed extension line actually
drawn, because that dashed line is the entire content of the relative-angle convention and it is what
you will forget. Label `L₁`, `L₂`, the elbow, and the tip. Then write the two FK equations beside it
and check by eye that each term corresponds to something on the drawing.

**Second, the workspace.** Draw the annulus to scale: outer 356.9 mm, inner 47.0 mm. Put your actual
bench on it — where the base clamps, where an object would sit — and confirm the object is outside the
inner circle. This drawing is what tells you whether your bench layout is possible, and it takes five
minutes.

> **CHECK YOURSELF** — Cover the equations and reconstruct them from your drawing. If you can walk the
> chain — out along `L₁` at angle θ₁, then out along `L₂` at angle `θ₁ + θ₂` — and write both lines
> without looking, you own this. If you cannot, you have copied it, and S2.3 will be much harder than
> it needs to be.

### What will go wrong

- **Your Python disagrees with your drawing at one specific pose and agrees everywhere else.** Almost
  always θ₂ measured absolutely in one and relatively in the other. The two conventions agree exactly
  when θ₁ = 0, which is the pose people test first.
- **Everything is out by a factor of 57.3.** `math.cos` takes radians. This is the same unit error as
  Stage 0 S6 and it will not feel familiar in a new language.
- **The workspace radii come out wrong and the FK is right.** You substituted degrees into
  `r = 2L·cos(θ₂/2)`, or halved the angle after taking the cosine rather than before.
- **The reachable annulus looks wrong on the bench.** Check you are measuring from the *shoulder
  pivot*, not from the edge of the base or the front of the plank. The inner radius is 47 mm from the
  axis, and the base is physically larger than that — which is the constraint the drawing exists to
  surface.

**Capture the broken state.** The one pose where your Python and your drawing disagree, with both
answers written on the same page. Photograph it. That disagreement is almost always θ₂ measured
absolutely in one and relatively in the other, the two conventions agree exactly at θ₁ = 0 which is
the pose everybody tests first, and a page showing the one pose that caught it is a much better
artifact than a page of correct trigonometry.

### Prove it

Python implementation. Then check three cases you can verify by inspection: fully extended along +x,
folded back on itself, and elbow at 90°. If any disagrees with the drawing, the drawing is right.

### Artifacts

- **`docs/sessions/forward-kinematics/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/derivations/forward-kinematics.jpg`
- `tools/kinematics.py` with the FK function.
- **Site:** the workspace annulus drawn to scale with your bench on it. It is the first thing in the
  project that shows you thought about where the robot *cannot* reach, and that reads as engineering
  in a way a reach figure does not.
  **The shot:** one still of the annulus drawn to scale, with your actual bench marked on it and
  an object placed outside the inner circle. Both radii written on the drawing. The inner hole is
  the interesting part, so do not let it get lost in the crop.

---

## S2.3 · Inverse kinematics, derived

**Goal:** given a target point, you can compute the angles that reach it — including deciding, and
enforcing, which of the two solutions you want.

**You will be able to:** derive inverse kinematics from the law of cosines, explain why there are two solutions and what picking the wrong one looks like on real hardware, and say what a singularity is in terms of a determinant going to zero.

### Concept

Inverse kinematics goes the other way, and this is where the difficulty lives. The answer may not
exist, and when it does there are usually several. For a two-link arm there are generally exactly two:
elbow-up and elbow-down.

### The math — the law of cosines route

```
r² = x² + y²                    (squared distance to target)

Elbow angle, from the law of cosines on the triangle (L₁, L₂, r):

  cos θ₂ = (r² − L₁² − L₂²) / (2·L₁·L₂)

  θ₂ = ± acos( ... )            ← the ± IS elbow-up vs elbow-down

Shoulder angle — and this is the one whose sign you will get wrong, so derive it rather than
copying it:

  θ₁ = atan2(y, x) − atan2( L₂·sin θ₂ , L₁ + L₂·cos θ₂ )
```

**Where θ₁ comes from.** It is the difference of two angles, and seeing them as two angles is the whole
derivation:

```
  φ = atan2(y, x)        the angle from +x to the TARGET, straight-line
  ψ = the angle from LINK 1 to that same straight line

  θ₁ = φ − ψ            walk out to the target, then back off by ψ

  and ψ comes from the same triangle, by dropping a perpendicular from the
  elbow onto r. The elbow sits at horizontal distance (L₁ + L₂·cos θ₂) and
  vertical distance (L₂·sin θ₂) from the shoulder, measured in a frame
  aligned with link 1 — which is exactly the two arguments of the second
  atan2, in that order.
```

Draw that triangle with φ and ψ marked on it before you write the line of Python. **The minus sign is
the entire content of the formula**, and it flips with the elbow branch — which is why the same
expression serves both solutions once θ₂ carries its own sign.

Three things to handle, and handling them is the exercise:

1. **Unreachable targets.** If `|cos θ₂| > 1` the point is outside the workspace (or inside the inner
   hole). Return failure rather than clamping — a clamped answer is a confidently wrong one.
2. **`atan2`, not `atan`.** `atan` loses the quadrant. This is a bug you will write once.
3. **Branch consistency.** Your solver must choose between the two solutions and choose
   *consistently*. Nearest-to-current-configuration is a good default rule.

> **WATCH OUT** — If the solver picks a different branch mid-trajectory, the arm flips configuration in a
> fast, alarming motion that can collide with itself or your desk. This is a **design decision, not an
> edge case.** Decide the rule, implement it, and write it in `docs/decisions/`.

### The math — the Jacobian, and where the arm goes stupid

> **DEFINITION** — **The Jacobian.** Forward kinematics is a non-linear map from joint angles to tip
> position. The **Jacobian** `J` is the matrix of its partial derivatives — the best linear
> approximation to that map at the pose you are currently in. One equation defines it, and it is the
> line immediately below this box.

```
    ẋ = J(θ) · θ̇          tip velocity = J × joint velocity
```

> **DEFINITION, continued** — Read that in both directions and you have most of what the Jacobian is
> for. **Forwards** it converts
> joint rates into tip motion. **Inverted** it answers the question you actually ask — "what joint
> rates produce the tip motion I want" — which is why a singular `J`, one you cannot invert, means an
> arm that physically cannot move its tip in some direction. And **transposed** it maps forces the
> other way, `τ = Jᵀ · F`, which is how Stage 5 turns a desired force at the fingertips into joint
> torques. Same matrix, three jobs. It is worth deriving yours by hand for this arm: it is 2×2, every
> entry is a sine or a cosine you already wrote in S2.2, and doing it once means the word stops being
> vocabulary.

For this arm the determinant is remarkably clean:

```
det(J) = L₁ · L₂ · sin θ₂
```

That is zero when **θ₂ = 0 (fully extended) or θ₂ = π (fully folded)**. At those configurations the
arm is **singular**: some directions of tip motion require infinite joint velocity, and near them a
small Cartesian move demands an enormous joint move.

Practical consequence, which goes straight into your joint limits: **never plan through full
extension.** Constrain the elbow so that `15° ≤ |θ₂| ≤ 165°` — at least 15° away from both fully
straight and fully folded, in either elbow-up or elbow-down configuration — and you have designed the
singularity out of your workspace rather than discovering it when the arm lunges.

### Draw this

**The IK triangle, with both solutions on the same page.** Draw the shoulder, the target point, and
the straight line `r` between them. That line plus `L₁` and `L₂` is a triangle, and the law of cosines
is applied to exactly that triangle — draw it and the algebra stops being symbol-pushing.

Then draw the *second* solution on top of the first, in a different colour: the same shoulder, the
same target, the same two link lengths, elbow reflected across the line `r`. Seeing the two triangles
share an edge is the clearest possible statement of why `± acos` gives two answers and why they are
mirror images about `r`.

Mark on the drawing which one your solver will return, and mark the elbow angle at which they
converge (θ₂ = 0, fully extended) — because that convergence *is* the singularity, and having drawn
it you will never again wonder why the determinant vanishes there.

### What will go wrong

- **`atan` instead of `atan2`.** `atan` loses the quadrant, so half your workspace mirrors into the
  other half. It is a one-character bug, everyone writes it once, and the round-trip test below catches
  it instantly — which is why the round-trip test exists.
- **The round trip passes and the arm still goes to the wrong place.** IK and FK share the same sign
  error, so they agree with each other and disagree with reality. This is why S2.2 says to check FK
  against *three poses you can verify by inspection* first — the round trip validates consistency, not
  correctness.
- **`acos` throws a domain error.** `|cos θ₂| > 1` because the target is unreachable, and you passed it
  straight in. Test the magnitude *before* the call and return failure, which is item 1 above.
- **Targets exactly on the workspace boundary fail intermittently.** Floating point: `cos θ₂` comes out
  as 1.0000000002. Clamp to ±1 before `acos` *after* you have already rejected genuinely unreachable
  points — the order matters, because clamping first turns "unreachable" into "fully extended" and
  hides the error you wanted.
- **The elbow flips mid-trajectory.** You have not enforced branch consistency. This is a design
  decision, not an edge case, and it is the WATCH OUT above.

**Capture the broken state.** The round-trip scatter with `atan` instead of `atan2` — half your
workspace mirrored into the other half. **Save that plot.** It is a one-character bug that produces
a strikingly symmetrical picture, it is instantly legible to anybody who has written kinematics, and
the corrected scatter beside it is a before-and-after that needs no caption.

### Prove it

Round-trip test: for a few hundred random reachable points, run IK then FK and confirm you land back
within a millimetre. This is the standard check and it will catch every sign error you have.

> **CHECK YOURSELF** — Pick a target at (0.2, 0.2) m and answer, on paper, before you run anything:
> is it reachable? Which branch will your solver return? And what would the *other* branch look like on
> the bench — not "mirrored", but which way would the elbow point? If you cannot answer the third one
> from your drawing, draw it again.

### Artifacts

- **`docs/sessions/inverse-kinematics/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/derivations/inverse-kinematics.jpg` — a full page of algebra.
- Round-trip test in `firmware/../tools/test_kinematics.py`, with the error histogram.
- **Site:** the IK derivation. Handwritten algebra for a machine you then built is the single most
  differentiating thing in this whole project.
  **The shot:** one still of the full page of algebra, square on and well lit. It must be readable
  end to end — this is the artifact the workbook calls the most differentiating thing in the
  project, and an unreadable photograph of it is worth nothing. Two shots of half a page each is
  better than one blurry shot of the whole one.

---

## S2.4 · The torque budget — the session that changes your parts list

**Goal:** you know how much torque each joint needs, and you have chosen motors on evidence.

**You will be able to:** compute a static torque budget from a mass table, distinguish rated from stall torque and say which you designed to and why, and defend a rejected option with the arithmetic that rejected it rather than with an assertion.

### Concept

> **DEFINITION** — **Free-body diagram, moment arm, centre of gravity.** A **free-body diagram** is the
> arm drawn in isolation with every force acting on it marked as an arrow and nothing else on the
> page — no bench, no motors, no context. Isolating it is the point: it is what stops you
> double-counting a force or forgetting one. A **moment arm** is the *perpendicular* distance from the
> pivot to the line of a force, and torque is force times moment arm. Perpendicular is the word that
> matters: hold the arm vertically and every weight still acts downward, but its perpendicular
> distance from the shoulder axis is zero, so the torque is zero. That is exactly why horizontal is
> the worst case. The **centre of gravity** is the single point at which a body's whole weight can be
> treated as acting — for a uniform link that is its midpoint, which is why link 1's 60 g sits at
> 90 mm rather than at 180 mm.

Static torque is the torque needed just to *hold* the arm against gravity, before any acceleration.
It is the floor, and for a horizontal arm it is the worst case. If your motor cannot meet the static
requirement, no amount of tuning helps.

### The math — do this with your own numbers

Torque about a joint is the sum of each downstream mass times gravity times its horizontal distance
from that joint.

```
FIGURE S2.4.1 — Free body, arm fully extended horizontally (the worst case)

   EVERY MASS BELOW IS ASSUMED, NOT MEASURED. See the table underneath,
   and re-run this page the moment CAD gives you real figures.

      SHOULDER                    ELBOW                       TIP
         ●═══════════════════════════●═══════════════════════════●
         │             │             │             │             │
         │        link 1 c.g.        │        link 2 c.g.        │
         │           60 g            │           60 g            │
         │             │        elbow motor        │       gripper 80 g
         │             │           80 g            │      + payload 100 g
         ▼             ▼             ▼             ▼             ▼
         │◄── 90 mm ──►│             │             │             │
         │◄──────── 180 mm ─────────►│             │             │
         │◄─────────────── 270 mm ────────────────►│             │
         │◄────────────────────── 360 mm ───────────────────────►│
                                     │◄── 90 mm ──►│             │
                                     │◄──────── 180 mm ─────────►│

   Drawn to scale: 90 mm is 14 columns, so every arrow below lines up with
   the mass it measures to. Read each dimension line from the shoulder for
   the shoulder sum, and the last two from the elbow for the elbow sum —
   they are two different diagrams sharing one drawing, and mixing them is
   how the elbow figure ends up using shoulder distances.

   τ = Σ (m · g · horizontal distance from the joint)

   ELBOW    0.060·9.81·0.090 + 0.080·9.81·0.180              = 0.194 N·m
            + payload 0.100·9.81·0.180                       = 0.371 N·m

   SHOULDER 0.060·9.81·0.090 + 0.080·9.81·0.180
            + 0.060·9.81·0.270 + 0.080·9.81·0.360            = 0.636 N·m
            + payload 0.100·9.81·0.360                       = 0.989 N·m

   Horizontal is the worst case because the moment arm is the full length.
   Straight up or straight down, the arm carries itself and τ → 0.
```

**Worked example, arm fully extended horizontally, `L₁ = L₂ = 180 mm` (14.2 in total reach).**
180 mm rather than 178: round numbers, for the reason S2.5 gives.

| Mass | Value | Distance from shoulder | Distance from elbow | Source |
|---|---|---|---|---|
| Link 1 structure | 60 g | 90 mm (its centre) | — | **assumed** |
| Elbow motor + bracket | 80 g | 180 mm | — | **assumed** |
| Link 2 structure | 60 g | 270 mm (its centre) | 90 mm | **assumed** |
| Gripper assembly | 80 g | 360 mm | 180 mm | **assumed** |
| Payload | 100 g | 360 mm | 180 mm | **your design target** |

> **WATCH OUT** — **Every mass in that table is assumed, not measured or CAD-derived.** They are
> plausible — a verified N20 is 10 g, so 80 g is generous for motor-plus-bracket and roughly right for
> an SG90-based gripper assembly; 60 g is defensible for a 180 mm PETG-CF link at typical infill,
> though it excludes fasteners, inserts, bearings and cable. **Re-run this whole page the moment your
> CAD tool can give you real masses**, which is the end of S2.5. Until then, treat every number below
> as an order of magnitude, not a value.

```
ELBOW — what hangs beyond the elbow joint:
  τ = 0.060 × 9.81 × 0.090        (link 2, at its centre)
    + 0.080 × 9.81 × 0.180        (gripper assembly, at the tip)
    = 0.053 + 0.141
    = 0.194 N·m          unloaded

SHOULDER — everything, measured from the shoulder pivot:
  τ = 0.060 × 9.81 × 0.090        (link 1)
    + 0.080 × 9.81 × 0.180        (elbow motor)
    + 0.060 × 9.81 × 0.270        (link 2)
    + 0.080 × 9.81 × 0.360        (gripper)
    = 0.053 + 0.141 + 0.159 + 0.283
    = 0.636 N·m          unloaded
```

**Now add the payload, because an arm that cannot lift anything is a fan.** Stage 3 is pick-and-place;
the whole point is that it picks something up. A 100 g object at the tip:

```
ELBOW    with payload: 0.194 + (0.100 × 9.81 × 0.180) = 0.371 N·m   (+91 %)
SHOULDER with payload: 0.636 + (0.100 × 9.81 × 0.360) = 0.989 N·m   (+56 %)
```

Design to the loaded figure. **0.99 N·m at the shoulder** is the number that matters.

### Now compare to your motor — and be careful which figure you compare to

This is where it is easy to flatter yourself, so do it twice.

The vendor listing for the N20 at 12 V / 100 RPM gives **stall torque 2 kg·cm = 0.196 N·m** *and*
**rated torque 0.1 kg·cm = 0.0098 N·m**. Those are different claims about different things:

- **Stall torque** is the torque at zero speed and maximum current. It is a limit, not an operating
  point. Holding a motor there overheats the winding, and small N20 gearboxes are explicitly rated
  for damage under sustained stall.
- **Rated torque** is the manufacturer's own continuous design point. It is the honest number.

```
Optimistic — 25 % of stall (a common hobby rule of thumb, NOT a standard):
  0.196 × 0.25 = 0.049 N·m
      Elbow  (loaded 0.371)  →   7.6× short
      Shoulder (loaded 0.989) →  20×   short

Honest — the manufacturer's own rated torque:
  0.0098 N·m
      Elbow  (loaded 0.371)  →  38×  short
      Shoulder (loaded 0.989) → 101×  short
```

> **WATCH OUT** — **The 25 %-of-stall rule is a convention, and not a very well-founded one.** Quote it if
> you like, but know that it is a heuristic you chose, not a standard you followed, and that the same
> vendor page gives you a continuous figure five times lower. If an interviewer asks where 25 % came
> from, "it is a rule of thumb; the manufacturer's rated figure is 0.0098 N·m and here is what changes
> if I use that instead" is a much stronger answer than defending the heuristic.

**Your Stage 0 motors cannot build this arm.** That conclusion is robust, and it is worth testing it
against the loaded figure rather than the unloaded one, since the loaded figure is the one you just
said to design to. Halve every *assumed* mass — the payload is a design target, not an assumption, so
it stays — and the shoulder requirement is `0.318 + 0.353 = 0.671 N·m`, still **13.7× short** on the
optimistic torque figure. It survives shortening the links, and it gets dramatically worse on the
honest torque figure. That is not a failure; it is
the calculation doing its job, three evenings before you would have found out by watching an arm sag.

### The math — the other half of the budget, which static torque does not cover

Everything above is **static**: what it takes to *hold* the arm. An arm that only holds is a shelf.
The moment you ask it to move you are also paying for acceleration, and that term is missing from every
number so far.

Newton's second law has a rotational twin. Where force is mass times linear acceleration, **torque is
rotational inertia times angular acceleration**:

```
   τ_dynamic = I · α

   I  = rotational inertia [kg·m²] — how hard this arm is to spin up about
        the shoulder. For point masses on a massless arm it is Σ m·r², and
        note the r is SQUARED, which is why mass at the tip dominates twice
        over: once in the static sum, and much harder here.

   α  = angular acceleration [rad/s²] — how fast you want to get to speed.
```

Compute `I` about the shoulder from the same mass table, with the Path A masses:

```
   link 1     0.060 × 0.090²  =  0.000486
   elbow mtr  0.200 × 0.180²  =  0.006480      ← the 200 g motor
   link 2     0.060 × 0.270²  =  0.004374
   tip        0.180 × 0.360²  =  0.023328      ← gripper + payload, and it is
                                 ─────────       two thirds of the total
   I about the shoulder        =  0.0347 kg·m²
```

Now pick an acceleration. `α` is not a property of the arm — it is a **choice about how fast you want
it to feel**, and it is the first genuinely free parameter in this whole budget:

```
   reach V_MAX (1.1 rad/s, post-Path-A) in ...

      0.5 s  →  α = 2.20 rad/s²  →  τ_dyn = 0.076 N·m  →  total 1.28 N·m  →  margin 2.3×
      0.3 s  →  α = 3.67 rad/s²  →  τ_dyn = 0.127 N·m  →  total 1.33 N·m  →  margin 2.2×
      0.1 s  →  α = 11.0 rad/s²  →  τ_dyn = 0.381 N·m  →  total 1.58 N·m  →  margin 1.9×

   (static-only margin was 2.45×)
```

**So the dynamic term costs you between 6 % and 32 % of your margin depending on how briskly you want
the arm to move**, and you cannot know which until you decide. Decide now, write it down, and note
that it is the number MoveIt's acceleration limits in S2.13 will be set from — those are the same
quantity seen from the other end, and if you leave them as placeholders you are implicitly choosing
one anyway.

> **CHECK YOURSELF** — Two questions the arithmetic answers and intuition does not. **One:** the tip
> mass is 180 g of 500 g total — under 40 % — yet it contributes two thirds of `I`. Why? **Two:** the
> elbow's own dynamic term is much smaller than the shoulder's even for the same α. Say why in one
> sentence before you compute it. Both answers are the same word, and it is the word that makes mass
> at the tip the most expensive mass on the arm.

### The math — the supply, which is the check nobody does

Stage 0's power budget was one N20: 12 W against a 60 W adapter, comfortable by five. **That budget is
void the moment you change motors, and nothing else redoes it.** Do it — the answer is not alarming,
but it is the one number in this project with no margin left in it.

Itemise the 5 V rail first, because a single padded guess is how this calculation goes wrong in either
direction:

```
   5 V RAIL                                    STM32 Nucleo         50 mA
                                               gateway ESP32-S3    100 mA
                                               2 × hall encoders    30 mA
                                               2 × SN65HVD230       20 mA
                                               3 × INA219            5 mA
                                               misc / LEDs          20 mA
                                                                   ──────
                                               logic subtotal      225 mA
   gripper servo: ~10 mA idle · ~150 mA holding · ~650 mA stalled

   Reflected to the 12 V rail through an ~85 %-efficient buck:
        12 V draw = 5 V × total ÷ 12 ÷ 0.85
```

Then the four cases that matter:

```
   12 V 5 A adapter = 5.0 A available, 60 W

   running normally (both motors at rated 1.0 A)   2.18 A    44 %   ✓
   ONE joint stalled                               3.48 A    70 %   ✓
   BOTH joints stalled, gripper holding            4.78 A    96 %   ← no margin
   BOTH stalled AND the gripper stalled too        5.03 A   101 %   ← over
```

**Read that honestly, in both directions.** Normal operation is comfortable and one stall is fine — the
adapter is not marginal for anything you do on purpose. What has gone is the *fault-case* margin: a
double stall lands you at 96 % of a rating that is itself specified at 25 °C and derates as the brick
warms up in an enclosure.

Whether 96 % is a problem depends entirely on **how long it lasts**, and that is a software question
rather than a hardware one:

- **If your S11 stall latch fires**, the excursion is tens of milliseconds, your bulk capacitance
  carries most of it, and a 60 W adapter will ride through without the rail moving enough to matter.
- **If it does not fire** — a bug, a window sized too long, a fault path you did not test — the adapter
  is asked for ~100 % continuously. It will fold back or shut down, your 5 V logic comes off that same
  12 V, and **the controller browns out at exactly the moment it was supposed to be latching the
  fault.** That is a protection mechanism depending on surviving the event that triggers it.

So the real conclusion is not "buy a bigger supply." It is: **this is now the number with no headroom,
and the S11 latch is what stands between you and finding out.** Three responses, and you should pick
one deliberately rather than by default:

| Response | Cost | What it actually buys |
|---|---|---|
| **Measure it, then decide** | free | The honest first move. You will own the motors by then: stall one and watch the 12 V rail, then stall both. If it sags under a hundred millivolts, you have your answer. |
| **A separate 5 V supply for logic** | ~C$12 | Fixes the *failure mode* rather than the number. The motor rail can collapse and the controller stays up to notice, which is the property you actually want. |
| **A 12 V 8–10 A supply** | ~C$25, Tier D2 optional | Buys margin, the same way the bigger motor driver does — not because the current one is incompatible, but because 96 % in a fault case is not a margin you want on a part running warm for hours. |

> **CHECK YOURSELF** — Two questions before you spend anything. **One:** what does *your* adapter do at
> 100 % — fold back, hiccup, shut down and latch, or just get hot? You cannot know from the label, and
> ten minutes with a meter and a stalled motor tells you. **Two, and it is the better question:** what
> is the *longest* your S11 latch can allow a double stall to last? If you can state that number, the
> supply question answers itself; if you cannot, the supply is not the thing to fix first.

> **WHERE THIS POINTS** — Notice what just became a motor selection criterion. S2.4 compared candidates
> on torque, then on speed, then on driver current. **Stall current is a fourth axis**, and it feeds
> straight into supply sizing and thermal design. A motor that met your torque requirement at 1.5 A
> stall rather than 2.3 A would have made this whole section unnecessary. Weigh it next time — that is
> the kind of second-order consequence that separates specifying a part from picking one.

### What will go wrong

Every failure in this session is an arithmetic failure that produces a *plausible* number, which is
the worst kind — nothing errors, and you buy the wrong motors.

- **kg·cm on one side and N·m on the other.** The requirement is in N·m and every listing is in kg·cm.
  Convert once, at the top, and never carry both. This is Stage 0 S6's rule with different units.
- **The elbow sum uses shoulder distances.** They are two different free-body diagrams that happen to
  share a drawing. The elbow does not carry link 1 or the elbow motor at all, and if your elbow figure
  is more than half your shoulder figure you have almost certainly done this.
- **You compare against stall torque because it is the number on the listing.** It is a limit, not an
  operating point. The whole session turns on this and it is still the easiest slip to make.
- **You forget the payload.** An arm that cannot lift anything is a fan. Design to the loaded figure —
  and when you sanity-check the conclusion later, keep using the loaded figure rather than quietly
  switching to the unloaded one because it is more flattering.
- **You reject an option without multiplying it out.** Belt reduction is the specific trap: it *feels*
  like it should close the gap. Multiply every option through before you accept or reject it, which is
  the entire lesson of this session.
- **You solve the problem and forget the solution has mass.** A bigger motor is heavier and the
  shoulder carries it. Redo the sum after you choose, not before.

**Capture the broken state.** This session is three evenings of arithmetic and its artifact is a
page of handwriting — so the broken state is **on the page, and the instruction is not to erase
it.** Strike through the elbow sum that used shoulder distances, or the total that came out in kg·cm
on one side and N·m on the other, and leave it legible with the correction beside it. A photographed
page carrying a struck-through wrong line and a right one is worth more than a clean page, because
it is evidence of checking rather than of transcription, and there is no way to reconstruct it once
you have rubbed it out.

### Prove it

There is no rig to test here, so the acceptance test is arithmetic — and it is a real one, because
each check catches a specific error above.

1. **The vertical check.** Recompute the shoulder sum with the arm pointing straight up. Every moment
   arm is zero, so the answer must be **exactly zero**. If it is not, you have a distance in your sum
   that is not a *horizontal* distance, which is the commonest error in a torque budget.
2. **The 45° check.** Recompute at 45°. Every term should fall by exactly `cos 45° = 0.707`, so the
   total should be 0.707 × your horizontal figure. If it is not, you are applying the angle to some
   terms and not others.
3. **The ratio check.** Your elbow figure should be substantially smaller than your shoulder figure,
   because the elbow carries only what is beyond it. Predict roughly what fraction before you look.
4. **The units check.** kg × m/s² × m = N·m. Write the units out once, in full, beside the sum.

> **CHECK YOURSELF** — Before you read the comparison section: your motor's listing says 2 kg·cm. Your
> shoulder needs 0.99 N·m. **Convert and guess the shortfall to the nearest order of magnitude before
> you turn the page.** Being wrong is fine and instructive; not having guessed means the number that
> follows will not land.

### Draw this

**Your own free-body diagram, before you look at FIGURE S2.4.1 again.** Draw the arm horizontal.
Mark every mass as a downward arrow at its centre of gravity. Then, underneath, draw the moment arms
as horizontal dimension lines — measured from the shoulder for the shoulder sum, and *again* from the
elbow for the elbow sum, because those are two different diagrams and drawing them as one is how the
elbow figure ends up using shoulder distances.

Then write the sum term by term in your own handwriting and total it. Do not transcribe the numbers
above; produce them. This is the single most valuable page of paper in Stage 2, because it is the one
that changed the parts list, and an interviewer who asks "why these motors?" is asking to be shown
exactly this.

Finally, redraw it once with the arm vertical and confirm every moment arm goes to zero. That is a
thirty-second sanity check on whether you have understood what a moment arm is, and it costs nothing.

### The five ways out — and the arithmetic that kills two of them

**Do not stop at the list. Multiply each option through and see whether it actually reaches 0.99 N·m.**

| Option | What it gives you at the shoulder | Enough? |
|---|---|---|
| **Bigger motors** — JGB37-520 / GB37Y3530 class, 12 V, high ratio | The 270:1 variant is listed at **30 kg·cm rated ≈ 2.94 N·m** | **Yes, with margin — but read the speed row below** |
| **Belt reduction at the joint** — GT2, 3:1 or 4:1 | 0.049 × 3 = 0.147 N·m; × 4 = 0.196 N·m | **No — still 5× to 6.7× short** |
| **Shorter links** — 125 mm each, 10 in reach | Unloaded shoulder drops to 0.44 N·m; loaded, ~0.69 N·m | **No, but it helps every other option** |
| **Counterbalance** — spring or counterweight at the shoulder | Cancels the *unloaded* 0.64 N·m near one pose | **Partially, and only near that pose** |
| **Base-mounted motors + parallel linkage** | Removes the 80 g elbow motor from the moving arm: shoulder drops to ~0.49 N·m unloaded | **No alone, but it stacks well** |

> **WATCH OUT** — **A single-stage GT2 belt reduction does not solve this, and it is the option most
> likely to look as though it should.** You need roughly **20× at the shoulder** on the
> optimistic torque figure, and single-stage GT2 tops out around 4:1 or 5:1 before the small pulley
> runs out of teeth in mesh. Two stages of 4:1 would get you there mechanically and would be a serious
> build with backlash at every stage.
>
> **DEFINITION** — **Belt reduction and GT2.** A toothed belt running between a small pulley on the motor
> and a large one on the joint trades speed for torque in the ratio of their tooth counts, the same
> way a bicycle's gears do. **GT2** names the tooth profile — 2 mm pitch, curved teeth designed not to
> slip — and it is the standard in 3D printers, which is why it is cheap and available. The limit on a
> single stage is the *small* pulley: below about 16 teeth too few are engaged at once, and the belt
> skips under load. That is where the 4:1-to-5:1 ceiling comes from — it is a geometric limit, not a
> catalogue one. **Belt reduction is a good technique and it is the wrong tool for
> a 20× gap.** Check the multiplication on any option before you commit money to it — that is the
> entire lesson of this session.

#### But do the stacked case properly, because "does not work alone" is not "does not work"

The three options marked *"helps"* above stack, and it is lazy to reject the combination without
multiplying it out. So multiply it out. Best realistic case: **125 mm links, the elbow motor moved to
the base via a parallel linkage, a counterbalance spring at the shoulder, and a 4:1 GT2 reduction.**

```
Shoulder, 125 mm links, elbow motor removed from the arm:
  link 1     0.060 × 9.81 × 0.0625  = 0.0368
  link 2     0.060 × 9.81 × 0.1875  = 0.1104
  gripper    0.080 × 9.81 × 0.250   = 0.1962
                                      ───────
  unloaded                            0.343 N·m
  payload    0.100 × 9.81 × 0.250   = 0.2453
  loaded                              0.589 N·m

A counterbalance cancels the UNLOADED term near one pose, leaving the payload:
  requirement near that pose                 0.245 N·m

Available, N20 + single-stage GT2. Quote BOTH torque figures at BOTH ratios,
because quoting the flattering ratio for one and the harsh ratio for the other
is exactly the self-deception this session exists to prevent:

                       optimistic (25 % of stall)   rated (manufacturer)
  4:1        0.049 × 4 = 0.196  → 1.25× short     0.0098 × 4 = 0.039 → 6.3× short
  5:1        0.049 × 5 = 0.245  → break-even      0.0098 × 5 = 0.049 → 5.0× short
```

**Read that carefully, because it is the honest answer and it is more interesting than "no."** On the
optimistic figure the full stack does *not* fail by an order of magnitude — it lands within 25 % at
4:1 and exactly on the number at 5:1. On the rated figure it is 5× short at that same 5:1. It fails for three other reasons, and those are the reasons to
put in the ADR rather than a multiplication:

1. **Zero margin is not a design.** Break-even means it holds one pose, motionless, with a perfectly
   tuned counterbalance and no acceleration budget at all. An arm needs torque to *move*, not just to
   hang.
2. **The counterbalance only works near one pose.** Away from it the unloaded term comes back and the
   requirement climbs toward 0.589 N·m, which 5:1 misses by 2.4×.
3. **The optimistic figure is the one you should not be designing to.** On the manufacturer's own
   rated continuous torque the stack is **5× short even at 5:1**, the ratio that broke even on the
   flattering figure. There is no argument left.

So the conclusion holds — but it holds *on the rated figure and on the margin argument*, not because
the multiplication is hopeless. **Say it that way.** "I computed the best-case stack, it came to
break-even at 5:1 on an optimistic torque figure and 5× short at the same ratio on the honest one, so
I rejected it"
is a far better answer than "belt reduction is not enough," and it is the difference between having
done the arithmetic and having asserted a conclusion.

You also pay for the stack in CAD: a parallel linkage, a tuned spring, and shorter links that cut
your reach from 360 mm to 250 mm. **It is cheaper in parts and considerably more expensive in
everything else**, which is the real reason it is not the recommendation.

**And the consequence people miss on the option that does work:** a JGB37-520 is a 37 mm-diameter
gearmotor. Your budget assumed an 80 g elbow motor; this one is several times that. At 200 g the
shoulder requirement rises from 0.636 to **0.848 N·m unloaded, 1.20 N·m loaded** — a 33 % increase you
created by solving the problem. Against the 270:1 variant's rated **2.94 N·m** that is a **2.4× margin**,
so the answer survives comfortably, **but you only know that because you redid the arithmetic.** Redo
it for whichever option you choose.

> **WATCH OUT** — **You will see both "30 kg·cm" and "35 kg·cm" quoted for this motor. Design to 30.**
> Vendor tables for the 12 V / 37 RPM / 270:1 variant commonly list both in the same block —
> `Rated Torque: 30.0 Kg.cm` and `Maximum Torque: 35 Kg.cm` — alongside a 2.3 A stall current. Both are
> torques, and the words in front of them carry the whole meaning: 35 is a **maximum** rather than a
> continuous figure, which puts it in the same category as stall torque — a limit, not an operating
> point.
>
> **So: rated 30 kg·cm ≈ 2.94 N·m, listed maximum 35 kg·cm ≈ 3.43 N·m, and you design to the rated
> one** — for the same reason S2.4 designs to the N20's rated figure rather than its stall figure. The
> conclusion is unaffected either way: 2.94 N·m against 1.20 N·m required is a **2.4× margin**, and
> using the flattering number would only inflate it to 2.9×. **Say which figure you used, and why.**
> If a listing gives you one number without saying whether it is rated or maximum, treat it as maximum
> — that is the flattering one, and flattering is what listings do.

### The other thing that changes when you change motors

Changing the motor does not only change torque. Work through this list before you order, because
every item is a number already baked into working Stage 0 and Stage 1 firmware:

| What changes | Why |
|---|---|
| `COUNTS_PER_OUTPUT_REV` | The JGB37-520 encoder is **11 PPR per channel**, not 7. At 11 × 4 × 270 that is **11,880** counts/output rev, not 8,400. **The vendor's own listing quotes `11 × reduction ratio = 2,970`, with no ×4** — that is a ×1 figure and it is exactly the PPR/CPR trap. Yours will measure 11,880 because you decode all four edges. Measure it, do not read it. |
| **Every tuned PID gain** | `Kp` is command per radian. Change counts-per-radian and every gain is wrong by that factor. Retune. |
| The S1.3 correctness test | "The STM32 reads the same counts/rev as the UNO did" is still a valid test — against the *new* number. |
| **Joint speed — and this one is a real loss** | The 270:1 variant is listed at **37 RPM no-load, 28 RPM rated**, against the N20's 100 RPM — **2.7× slower at the joint**. Be precise about which number moves. The **no-load ceiling** falls from 10.47 rad/s to about **3.87 rad/s**; `V_MAX` is the limit *you chose* in Stage 0 S11, and it was 3.0 rad/s — 29 % of the old ceiling. **3.0 rad/s is now 77 % of no-load, which a loaded motor never reaches**, so the rate limiter you built would quietly stop limiting anything. Keep the same margin and `V_MAX` becomes about **1.1 rad/s**. That is the real loss, and it propagates: S1.8's command timeout (0.15 rad of travel at 3 rad/s) and S2.12's homing overshoot are both computed against `V_MAX` and both move with it. Decide whether an arm that slow suits Stage 3's pick-and-place *before* you order, not after. |
| Velocity limit, stall detection | Both derived from output speed and counts. Re-derive against 37 RPM and 11,880. |
| **The motor driver** | See below. |
| Backdrivability (Stage 5) | Expect a 37 mm gearmotor to be **harder** to backdrive than the N20, not easier, because reflected friction rises with gearbox size and stage count. Do not assume a mechanism for it: listings for this body are inconsistent about whether the train is worm or spur, and the ratio table these figures come from is a spur gearbox. **Test it rather than reasoning about it** — back-drive the shaft by hand when it arrives and write down what you feel. That measurement is what Stage 5 actually needs. |

> **WATCH OUT** — **The JGB37-520 has the same part-number problem your N20 does, and you should not
> repeat the mistake in the other direction.** "JGB37-520" is a *body* designation, not a motor: the
> same string is sold as a 10:1 / 1000 RPM / 1.6 kg·cm unit and as a 270:1 / 37 RPM / 30 kg·cm unit,
> an order of magnitude apart on torque and 27× apart on ratio. Every figure in this section comes
> from listings for the **270:1, 12 V, 37 RPM** variant specifically. **When you order, match the
> ratio and the RPM, not the part number**, and screenshot the listing you bought from — the same
> discipline S1's `docs/motor-spec.md` applies to the N20 applies here.

### Path A's cascading consequence: the driver

Get this one exactly right, because the tempting summary — "bigger motors, so all five drivers are
scrap" — is wrong, and being wrong in the *conservative* direction still costs you credibility.

```
JGB37-520, 270:1        rated current  ≤ 1.0 A
                        stall current    2.3 A
TB6612FNG               continuous       1.2 A
                        peak             3.2 A

Rated 1.0 A  vs  1.2 A continuous  →  INSIDE, by 17 % headroom
Stall 2.3 A  vs  3.2 A peak        →  INSIDE, but read the next paragraph
```

**Be careful with that second line, because the two numbers are not the same kind of number.** The
TB6612's 3.2 A is a **pulse rating** — the datasheet qualifies it with a duty cycle and a maximum
pulse width, on the order of tens of milliseconds. A stall is not a pulse. A stall persists until
something intervenes, and nothing about 2.3 A being under 3.2 A tells you the part survives holding
it. The honest statement is: **a stall on this motor exceeds the driver's continuous rating by
roughly 2×, and stays inside the pulse rating only if the stall is short.** What makes it short is
software: **your Stage 0 stall-detection latch (S11) is the thing that turns an over-rating into a
transient**, which is why the note below says it is not optional on this motor. Size the latch window
against the driver's pulse-width limit, not against what feels responsive.

**So the TB6612FNG is not invalidated. It is thermally marginal.** Normal operation sits inside its
continuous rating with 17 % to spare, and a *bounded* stall sits inside its pulse rating. That is a
real operating point, not a violation — and it is also not a margin you want on a part that will be
driving a heavier arm than it was sized for, in an enclosure, for hours.

**Buy a bigger driver anyway, and say why in that language.** A BTS7960 or DRV8871 class part gives
you room the TB6612 does not, and the argument is *margin*, not incompatibility. Budget it as part of
the motor decision rather than as a surprise afterwards — but keep the five TB6612s, because they are
still correct for the gripper servo's driver-free needs, for bench testing, and for Stage 0's rig,
which you should not dismantle.

> **WATCH OUT** — The manufacturer's own tables carry a **"blocking is not allowed / the motor is
> forbidden to be locked"** warning for this gearbox family. That is about the *gears*, not the
> winding: a high-ratio steel train can shed a tooth under a stall long before anything gets hot.
> Whatever driver you choose, your Stage 0 stall-detection latch (S11) is not optional on this motor.

> **WHERE THIS POINTS** — The trade-off is the interesting part, not the choice. An ADR (**Architecture
> Decision Record** — a short file recording a decision that had alternatives) that says "I computed
> 0.99 N·m at the loaded shoulder, my motors deliver 0.049 N·m optimistically and 0.0098 N·m by the
> manufacturer's rated figure, I checked that belt reduction only reaches 0.20 N·m and rejected it on
> arithmetic, I chose bigger motors and accepted a 33 % torque penalty from their mass and the loss of
> five drivers" is worth more in an interview than any amount of working code. **The rejected options,
> with their numbers, are the valuable part.**
>
> That file is an **actuation ADR in `docs/decisions/`**, and write it tonight, before you order
> anything. An ADR written before the money is spent is a decision; the same file written after the
> parts arrive is a justification, and the difference is visible in it.

### Artifacts

- **`docs/sessions/torque-budget/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/derivations/torque-budget.jpg`
- The actuation ADR in `docs/decisions/` — the number, the options, the choice, the consequences.
- Updated `hardware/bom.md`.
- **Site:** the free-body sketch in your handwriting, with the sum worked term by term, and one
  paragraph underneath naming the option you rejected and the arithmetic that rejected it. This is the
  strongest single artifact in Stage 2 — a decision with its reasoning attached, made before any money
  was spent, on a page that is dated. An interviewer asking "why these motors?" is asking to be shown
  exactly this.
  **The shot:** one still of the page, plus one paragraph of text beneath it. The sum must be
  readable term by term, **including anything you struck through**, and the rejected option's
  arithmetic must be on the same page as the chosen one. A photograph of a clean final answer is a
  different and much weaker artifact.

---

# PART II — SIMULATION

---

## S2.5 · CAD, and design for printing

**Goal:** two links, two joint housings, a rigid base, designed to be printed and to be assembled
more than once.

**You will be able to:** turn a CAD model into a source of *masses and inertias* rather than only shapes, and explain why print orientation is a structural decision rather than a convenience.

### Concept

You will print version three. Design version one to be ugly, fast, and easy to change.

### The rules that matter

- **Round link lengths.** You will type them into kinematics repeatedly. **180 mm**, which is what S2.4's budget assumes — not 178.4 mm. This is a link-geometry ADR in `docs/decisions/`: the length you chose, why a round number, and what S2.2's workspace annulus becomes at that length. Write it when you pick the number, because the two radii fall straight out of it and you will want them in Stage 3.
- **Heat-set inserts everywhere a screw enters plastic.** You bought M3 inserts and the T12 insert
  tip in the Stage 0 order. Screwing directly into printed plastic strips on the second assembly, and
  you will assemble more than twice.
- **Design the encoder mount first.** The AS5600 needs a diametric magnet on the joint axis at a
  controlled air gap — typically 0.5–3 mm, coaxial within a fraction of a millimetre. Retrofitting
  that mount is miserable.
- **Avoid overhangs**, and orient links so layer lines run along the load path, not across it.
- **Design the wire route.** Where does the encoder cable go as the joint rotates? A cable that
  fatigues at a joint is the most common cause of intermittent faults appearing weeks in.

### The math — a link is a beam, and you should find out how much it bends

"Avoid overhangs, orient the layers along the load" is style advice until you put a number on it. A
link is a **cantilever beam**: fixed at one end, loaded at the other, and it bends. How much is one
equation, and the answer changes your cross-section rather than confirming it.

```
   δ = F·L³ / (3·E·I)      tip deflection of a cantilever

   F  load at the tip [N]        — gripper + payload = 0.180 × 9.81 = 1.77 N
   L  length [m]                 — 0.180
   E  Young's modulus [Pa]       — how stiff the MATERIAL is.
                                   PETG-CF ≈ 3.5 GPa. PLA ≈ 3.5, PETG ≈ 2.
   I  second moment of area [m⁴] — how stiff the SHAPE is.
```

Those last two are the whole point and they are different things. `E` is a property of the plastic and
you cannot change it except by changing filament. **`I` is a property of the cross-section you drew,
and you can change it by a factor of forty in CAD for free.** For a rectangle, `I = b·h³/12`, where `h`
is the dimension **in the direction of bending** — and it is cubed, which is the entire lesson.

Note also the `L³`. Doubling a link's length makes it eight times floppier at the same section, which
is a second reason the shorter-links option in S2.4 helps more than it looks.

Run it for three sections a beginner might plausibly draw:

```
   180 mm link, 1.77 N at the tip, PETG-CF

   hollow box 15 × 25 mm, 2 mm wall     I = 11,042 mm⁴   δ = 0.09 mm
   solid bar   5 × 25 mm, on edge       I =  6,510 mm⁴   δ = 0.15 mm
   the SAME bar laid flat (25 × 5)      I =    260 mm⁴   δ = 3.77 mm
```

**Same material, same mass, same part — rotated ninety degrees, and forty times floppier.** That is
what `h³` means, and it is why "which way up does this link go" is a structural decision made in CAD
rather than a slicer setting made later.

**That makes it an ADR of its own, and it is not the same file as the link-geometry one.**
That one is about link *length* and the workspace it buys; this one is about the section and which
way up it prints, and a factor of forty deserves its own page. Write it when you draw the section,
with `I` computed both ways on it.

Two consequences worth carrying forward.

**One: 0.09 mm is invisible and 3.8 mm is not.** Your encoder resolves 0.03° at the joint, which at
360 mm is about 0.19 mm at the tip. A link that deflects 3.8 mm is putting twenty encoder counts of
error into a measurement your controller believes — and it will not see it, because the encoder is at
the *joint* and the bending is beyond it. This is the same blind spot as gearbox backlash, one link
further out.

**Two, and this is the one nobody tells you: a flexible link puts a resonance in your plant.** A beam
with a mass on the end is a spring with a mass on the end, and it has a natural frequency. Push a
controller's gains up and you will eventually excite it — the arm will buzz at a frequency that has
nothing to do with your loop rate and does not change when you change `Kp`. That is **exactly the test
you learned in Stage 0 S8** for telling gearbox backlash from controller oscillation, and it works here
for the same reason. Your `Ku` on the assembled arm may be set by the stiffness of a printed part
rather than by anything in your code, and if it is, no amount of tuning will move it. Stiffen the link.

> **CHECK YOURSELF** — Before you draw anything: you want to double a link's stiffness. Would you
> rather add 2 mm to its depth or 2 mm to its width, and by what factor does each help? Then the harder
> one — if you halve the wall thickness of a hollow box but keep the outside dimensions, roughly what
> happens to `I`? One of those two answers is much less intuitive than it looks and it is why hollow
> sections are efficient.

### The printer decision

Now, and not before — this is the point where it earns its keep. A budget enclosed CoreXY with a
hardened nozzle handles the engineering filaments an arm actually needs. **Verify the nozzle material
on whichever SKU you buy**; the hotend temperature rating is what matters for carbon-filled filament.

Materials: links in **PETG-CF** or **PA6-CF**, brackets in **PETG**, gripper pads in **TPU**.

> **DEFINITION** — **The filaments, and why each one is where it is.** **PETG** is the general-purpose
> engineering choice: tougher and more heat-resistant than PLA, far easier to print than ABS, and it
> does not creep under sustained load the way PLA does — which matters for a bracket holding a motor
> for months. **PETG-CF** and **PA6-CF** are the same base polymers with chopped **carbon fibre** mixed
> in: much stiffer and more dimensionally stable, and *abrasive*, which is why they need a **hardened
> nozzle** — the fibres saw through a standard brass nozzle in a few hundred grams. PA6-CF is nylon,
> stiffer and stronger still, and it absorbs water from the air so aggressively that it must be dried
> before printing or it will foam. **TPU** is rubber: flexible, high friction, and the reason the
> gripper pads are specified in it rather than in PETG.
>
> Three more words you will meet in the slicer. **Infill** is the internal lattice percentage — for a
> link loaded in bending, wall count matters far more than infill, because bending stress lives at the
> surface. **Layer lines** are the boundaries between printed layers and they are the weak plane:
> parts break *along* them, so **print orientation** is a structural decision, not a convenience one —
> orient a link so the load runs along the layers and not across them. **Clearance fit** is the
> deliberate gap you leave between two parts that must assemble; printers over-extrude slightly, so a
> hole modelled at exactly 5 mm comes out under 5 mm. Print a tolerance test block early and measure
> what your machine actually does, once, and reuse that number everywhere.

> **LOOK THIS UP** — Before designing anything, look at the open two-link and desktop-arm designs that
> already exist — the **SO-100/SO-101**, **AR4**, **BCN3D Moveo** and **Thor** are all published with
> source CAD. You are not copying them; you are looking at how other people solved joint housings,
> bearing seats, cable routing and motor mounts in printed plastic. An hour spent reading someone
> else's joint cross-section will save you a reprint, and noticing *why* they all put a bearing on the
> opposite side of the joint from the motor is worth more than any tutorial.

**Design the gripper mount now, even though you build the gripper in S2.10.** It needs a flat face on
the end of link 2, an insert for the servo, and a cable route. Retrofitting a mounting face onto a
printed link means reprinting the link.

### Draw this

**The link cross-section, at scale, with `I` computed on the page.** One rectangle — or one hollow
box — drawn to size, with `b` and `h` labelled, the bending direction marked with an arrow, and
`I = b·h³/12` worked underneath it. Then the deflection, from the equation above.

Then draw the *same section rotated ninety degrees* beside it and compute `I` again. Two numbers, one
part, and the ratio between them is the argument for the orientation you chose. Pin it next to the
bench; it is the page that stops you laying a link flat because it looked better in the slicer.

### Build

1. **Model the two links, both joint housings, and the base**, to the rules above. Ugly and simple.
2. **Set the material density** on every part, in the CAD tool, to the filament you intend to print
   it in — PETG-CF around 1.30 g/cm³, PETG around 1.27, PA6-CF around 1.15. This is the step that
   turns your model into a source of masses rather than a source of shapes, and it takes a minute.

   **Where this lives depends on your tool, and it is not always where you expect.** In Fusion 360 it
   is a *Physical Material* applied per body. In Onshape it is a part property, or an assembly-level
   override. In FreeCAD it is not a modelling property at all — the mass-properties panel takes a
   density you supply, and the FEM workbench's material definitions are a separate mechanism. Find it
   in the tool you actually chose before you rely on the number, and **sanity-check one part by hand**:
   volume × density should match what the panel reports, and if it does not you have set density on
   the assembly rather than the body, which silently gives every part the same one.

   Note also that a printed part is **not solid**. The density above is the filament's; your part is
   walls plus infill plus air. Treat the CAD figure as an upper bound, expect the printed part to come
   in lighter, and let S2.9's scale settle it — that is the third of the three passes.
3. **Read the mass and the inertia tensor for every part** out of the tool's mass-properties panel.
   Both are needed: the masses go into S2.4, the inertia tensors go into the URDF in S2.6, and
   S2.7 explains what happens in Gazebo when you guess them instead.
4. **Add the parts CAD cannot know about.** Fasteners, heat-set inserts, bearings, the motor itself,
   and cable. A rough count times a catalogue weight is fine; leaving them out is not, and the S2.4
   budget explicitly excludes them today.
5. **Export STEP** and commit it, with the native source file alongside, to `hardware/cad/`.

### What will go wrong

- **Every part has the same mass and it is wrong.** You set the density on the assembly rather than on
  each body, so the tool applied one default to everything. Check one part by hand — volume × density —
  before you trust the panel.
- **The CAD masses are 20–40 % higher than the printed parts.** Correct, and expected: the model is
  solid and the print is walls plus infill. Treat CAD as an upper bound and let S2.9's scale settle it.
- **The inertia tensor is about the wrong origin.** Most tools will give it about the centre of mass or
  about the part origin, and URDF wants it about the frame you declare in `<inertial><origin>`. Getting
  this wrong makes Gazebo behave oddly in a way that looks like a physics bug. Note which your tool
  reported.
- **You design the gripper mount later and have to reprint link 2.** The flat face, the servo insert
  and the cable route have to exist in the link, and retrofitting a mounting face means reprinting the
  whole part. This is a six-hour mistake and it is why the section above says to do it now.
- **You model to nominal dimensions and nothing fits.** That is what S2.9's coupon is for — but you
  need the *fits themselves* parameterised in CAD, so that applying a measured delta later is one
  number and not a remodel. Use a variable for clearance from the first sketch.
- **The link is beautiful and you have printed nothing.** The real failure of this session. Version one
  is meant to be ugly. Fifteen hours is budgeted; if you are past twenty, print what you have.

> **CHECK YOURSELF** — Before you export a single mass: guess link 1's, in grams. You know its length,
> roughly its cross-section, and PETG-CF's density. Being within a factor of two is a good result, and
> the point is that S2.4 assumed 60 g — so your guess is also a check on whether that assumption was
> anywhere near sane.

**Capture the broken state.** The mass-properties panel with every part reporting the same mass,
before you find that the density went on the assembly rather than on each body. Screenshot it. It is
a failure that produces confident, plausible, uniformly wrong numbers that then flow into your
torque budget and your URDF inertias, and nothing anywhere tells you.

### Prove it — this session owes S2.4 a number

**S2.4 says, in as many words, "re-run this whole page the moment your CAD tool can give you real
masses, which is the end of S2.5."** This is that moment, and it is the only reason the dependency is
worth stating. Do not carry the assumed 60 g / 80 g / 80 g figures into S2.6.

1. Substitute your CAD masses into the S2.4 sum, term by term, and recompute the loaded shoulder
   torque. Write both totals down — assumed and CAD-derived — and the percentage between them.
2. Re-check the margin. Path A's 2.4× against a 2.94 N·m rated motor is what justified the parts
   choice; if your real masses move it below about 1.5×, the actuation decision is back open and you
   want to know that before you buy, not after you print.
3. Sanity-check one part on a scale later, in S2.9, against what CAD predicted. A CAD mass that is
   20 % under the printed mass usually means the slicer's wall count and infill do not match what the
   density assumed — which is a five-minute fix now and a reprint later.

Note that this is the **second** of three passes over these masses: assumed in S2.4, CAD-derived here,
measured in S2.9. Each one is meant to move the number, and recording all three is a better artifact
than any one of them.

### Artifacts

- **`docs/sessions/cad-and-printing/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `hardware/cad/` — source files and STEP exports, committed.
- **A mass table**: every part, its CAD-derived mass, and its distance from each joint. This is what
  S2.4 consumes and what S2.9 will correct.
- **The re-run S2.4 budget**, with the assumed-versus-CAD comparison and the revised margin, appended
  to `docs/derivations/torque-budget.jpg` or as a second page beside it.
- The link-geometry ADR in `docs/decisions/` — link length, why a round number, and what the workspace
  annulus from S2.2 becomes at that length.
- **Site:** the CAD render beside the S2.4 free-body sketch. The same arm, drawn twice, once by hand
  with the arithmetic on it. That pairing reads as engineering in a way either one alone does not.
  **The shot:** two images at the same size: the CAD render at the same pose as the free-body
  sketch. Same orientation on both, or the pairing does not read.

---

## S2.6 · URDF, and seeing it in rviz2

**Goal:** an XML description of your arm, moving in the visualiser from a slider.

**You will be able to:** describe a robot as a tree of frames with a joint origin between each pair, and check that description against your own kinematics rather than against how it looks.

### Concept

> **DEFINITION** — **xacro.** URDF is XML with no variables, no arithmetic and no reuse, so a real robot
> description written directly in it is thousands of repetitive lines with your link length typed in
> eleven places. **xacro** is a macro preprocessor that adds `<xacro:property>` constants,
> `${}` expressions, and `<xacro:macro>` definitions, and expands to plain URDF before anything else
> reads it. Use it from the first line: define `L1` and `L2` as properties and every downstream
> dimension in terms of them, so that changing a link length is a one-line edit rather than an
> eleven-line one you will get wrong. `xacro my_robot.urdf.xacro` prints the expanded result, and
> reading that output is how you debug a description that is not doing what you meant.

URDF describes links, joints, axes, limits, and inertias. Nearly everything in the ROS 2 manipulation
stack reads it — the visualiser, the planner, the simulator, and the transform tree all derive their
understanding of your robot from this one file. Getting it wrong once means everything downstream is
wrong in the same way.

### The build

- `world` → `base_link` → `shoulder_link` → `elbow_link` → `gripper_tip`
- Revolute joints, `axis` = `0 0 1` for a planar arm in the XY plane.
- **Joint limits from S2.3** — including the `15° ≤ |θ₂| ≤ 165°` elbow limit that designs out the
  singularity.
- Run `robot_state_publisher` with `joint_state_publisher_gui` and drag the sliders.

> **WATCH OUT** — Frame conventions and joint axes are the thing to get right *here*, in isolation, with
> nothing else running. A sign error in a joint axis produces an arm that moves plausibly in
> simulation and mirrors itself in reality, and finding it later means debugging URDF, kinematics, and
> firmware simultaneously. Drag every slider through its full range and watch for anything that bends
> the wrong way.

### Draw this

**The link/joint tree as a graph**, before you write the XML. Boxes for links, arrows for joints,
each arrow labelled with the joint name, its type, and its axis. Then annotate each arrow with the
`origin` — the translation and rotation from the parent link's frame to the joint. That annotation is
the part people skip and it is where the errors live: a URDF is a tree of *frames*, and the joint
origin is the only thing that positions one frame relative to another.

Draw the frame axes explicitly at `base_link`, at the elbow, and at `gripper_tip` — three little sets
of x/y/z arrows. Then check one thing: with both joints at zero, does your drawing put the arm where
you expect? URDF's zero pose is whatever your origins say it is, and "the arm is folded on itself at
zero" is a design decision you should make on paper rather than discover in rviz2.

> **LOOK THIS UP** — The **Articulated Robotics** URDF videos and the official `docs.ros.org` URDF
> tutorials cover this well, and the ROS 2 documentation's *Building a Visual Robot Model with URDF
> from Scratch* is the shortest path to a working file. Do the drawing first — the tutorials will make
> immediate sense if you already have a frame tree on paper, and will be a blur of tags if you do not.

### Prove it

> **CHECK YOURSELF** — Before you drag anything: with both joints at zero, where does *your* URDF put
> the arm? Say it out loud, then look. URDF's zero pose is whatever your joint origins say it is, and
> "folded on itself at zero" is a design decision rather than a discovery — this is the moment to find
> out which one you made.

Drag the shoulder to a known angle, drag the elbow to a known angle, and check the tip position rviz2
reports against your own FK function from S2.2. They must agree.

That check is the whole session. It is your paper mathematics and the ROS 2 stack confirming each
other, and if they disagree you have found the discrepancy at the cheapest possible moment.

### Artifacts

- **`docs/sessions/urdf/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `robot_description` xacro committed, with `L1` and `L2` as properties rather than as typed numbers.
- The hand-drawn frame tree, photographed, into `docs/derivations/`.
- The rviz2-versus-your-FK comparison, as a short table of angles and tip positions.
- **Site:** a short screen capture of the arm following the sliders, next to your hand-drawn frame
  tree. The pairing is the point — anyone can show a robot model moving; almost nobody shows the
  drawing it came from.
  **The shot:** one screen capture, 10 to 15 seconds, of rviz2 with the sliders being dragged —
  the arm **and** the slider window in the same recording, so the causation is visible. Beside it,
  the still of your hand-drawn frame tree.

### What will go wrong

- **rviz2 shows nothing at all.** Set *Fixed Frame* to `base_link` — it defaults to `map`, which
  nothing in your tree publishes, and an unresolvable fixed frame renders an empty scene with only a
  small warning. This costs almost everyone their first twenty minutes.
- **rviz2 shows the robot but every link sits at the origin, stacked.** `robot_state_publisher` is
  running and receiving no joint states. Start `joint_state_publisher_gui`. If it is running, check
  that the joint *names* in `/joint_states` match the joint names in the URDF exactly — a mismatch
  fails silently rather than erroring.
- **Links are there but invisible.** A `<visual>` with no `<material>`, or a mesh path that did not
  resolve. Use `package://` paths, never relative ones, and check the terminal for the resource
  warning rather than trusting the render.
- **A joint bends the wrong way.** The `axis` sign. Fix it in the URDF, not in your IK — this is the
  same "one place, commented" discipline as Stage 0's encoder sign, and the URDF is the one place
  because everything downstream reads it.
- **The whole arm is a thousand times too big or too small.** URDF is metres. Your CAD is probably
  millimetres. The mesh `<scale>` is `0.001 0.001 0.001`.
- **`joint_state_publisher_gui` shows no sliders.** It only creates sliders for joints it considers
  movable — a joint accidentally typed `fixed` gets none, and that is usually the actual bug.

**Capture the broken state.** **rviz2 showing nothing at all**, because Fixed Frame is still `map`.
Screenshot the empty scene with its small warning. It is one of the most recognisable failures in
ROS 2, it costs almost everybody their first twenty minutes, and anyone who has used the tool will
know exactly where you were the moment they see it.

---

## S2.7 · Gazebo Harmonic

**Goal:** the arm moving in simulation, with physics, before a single part is printed.

**You will be able to:** say what a simulator needs that a visualiser does not — inertias, collision geometry, effort and velocity limits — and recognise which one is missing from the way the arm misbehaves.

### Concept

This is the single best decision available in this stage. Simulation lets you debug your kinematics,
your joint limits, your frame conventions, and your ROS 2 plumbing while the only cost of a mistake is
a rerun. When you then connect real hardware, any remaining problem is a hardware problem — which
halves your search space.

### Build

Spawn the URDF in `gz sim`, bridge topics with `ros_gz_bridge`, and command joint positions. Verify
gravity behaves: with the controllers off, the arm should fall. If it does not, your inertias or
masses are wrong, and wrong inertias make simulated tuning meaningless.

> **DEFINITION** — **Inertia tensors.** URDF wants a mass and a 3×3 inertia matrix per link. Your CAD tool
> computes both from the geometry and material density — export them rather than guessing. Guessed
> inertias are the reason simulated arms behave in ways that do not transfer to hardware, and it is a
> five-minute export.

> **DEFINITION** — **SDF, and how it relates to URDF.** **SDF** (Simulation Description Format) is
> Gazebo's own native format. It describes worlds as well as robots — lights, physics parameters,
> ground planes, sensors — where URDF describes only a single robot as a tree. Gazebo converts your
> URDF to SDF when it spawns it, which is why URDF stays your single source of truth and you should
> not maintain a hand-written SDF alongside it. What you *do* add to the URDF are `<gazebo>` tags:
> blocks that mean nothing to rviz2 or MoveIt and are passed through to the simulator, carrying
> friction coefficients, sensor plugins, and the `gz_ros2_control` system plugin. When something
> behaves differently in Gazebo than in rviz2, the difference is almost always inside a `<gazebo>` tag
> or in an inertia that rviz2 never reads.

### Draw this

**Predict the fall.** Before you spawn anything with the controllers off, draw the arm at its start
pose and sketch where you expect it to end up, and roughly how long it takes to get there. You have the
mass table, you know where the centre of mass is, and you computed the static torque in S2.4 — so this
is a prediction you can defend rather than a guess.

Then run it and compare. **A simulation that falls somewhere your free-body diagram says it should not
is telling you your inertias or your joint origins are wrong**, and that is much cheaper to find now
than in S2.11 when there is real hardware to blame.

### What will go wrong

- **The arm falls through the floor, or explodes on spawn.** Almost always inertia. A link with zero
  or absurdly small inertia values makes the solver unstable, and a `<collision>` geometry missing
  means there is nothing to collide with. Export real inertias from CAD; do not hand-write them.
- **The arm sags or jitters even with controllers active.** Your simulated joint has no damping and
  no effort limit. `<limit effort=... velocity=...>` in the URDF is read by the simulator, and
  omitting it gives you an infinitely strong, infinitely fast joint, which physics engines handle
  badly.
- **It spawns and does not move, and no controller errors.** The `<gazebo>` block carrying the
  `gz_ros2_control-system` plugin is missing. FIGURE S2.8.1 flags this: the Gazebo case is the one
  hardware plugin that is not just a single `<plugin>` line.
- **Topics exist on both sides and nothing crosses.** `ros_gz_bridge` is not running, or the type
  mapping in its config is wrong. The bridge is explicit by design — nothing is shared automatically.
- **You followed a tutorial and none of the commands exist.** It was written for Gazebo Classic. The
  tell is `gazebo` and `gazebo_ros` instead of `gz sim` and `ros_gz`, as S2.0 warned.

**Capture the broken state.** The arm exploding on spawn, or falling through the floor, from an
inertia tensor that is zero or absurd. Screen-record it — this is the one failure in Stage 2 that is
funnier as video than as a still. It is also the clearest possible statement of what a simulator
needs that a visualiser does not, which is the whole session in five seconds.

### Prove it

Three checks, in this order, because each one isolates a different layer:

1. **Gravity works.** Controllers off, spawn the arm, and it falls. If it does not fall, your masses or
   inertias are wrong and every tuning run you do in simulation afterwards is meaningless. **Predict
   which way it falls before you press play** — you know where the centre of mass is.
2. **The bridge works.** `ros2 topic echo` on the joint states shows numbers changing as it falls.
   Topics existing on both sides is not the same as messages crossing.
3. **Commands work.** Send a joint position and the arm goes there. Then send one *outside* the limits
   you wrote in the URDF, and confirm it does not.

> **CHECK YOURSELF** — Compare the falling arm against a number you already have: S2.4 says the
> unloaded shoulder torque is about 0.64 N·m horizontal. Does the simulated arm's behaviour look like
> a thing that heavy on a joint that strong? You are not measuring anything precisely — you are
> checking that simulation and arithmetic describe the same object, and a gross mismatch here is much
> cheaper to find now than in S2.11.

> **LOOK THIS UP** — The `ros_gz` repository's own README and demo package are more reliable than most
> tutorials for this pairing, because the Classic-to-Harmonic transition left a great deal of stale
> writing behind. Prefer the Gazebo documentation for the version you are actually running over
> anything on a blog.

### Artifacts

- **`docs/sessions/gazebo/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- The `<gazebo>` blocks and the bridge configuration, committed with the URDF.
- `docs/decisions/` — the inertia source (CAD-exported, not hand-written) and the effort and velocity
  limits you set, with where they came from.
- **Site:** the arm falling under gravity with controllers off, then holding with them on. Ten seconds,
  and it is the most legible possible demonstration that the simulation has physics in it rather than
  just geometry.
  **The shot:** one screen capture, about 10 seconds, one take: controllers off and the arm falls,
  then controllers on and it holds. Do not cut between two recordings — the single take is what
  makes it a demonstration rather than an assertion.

---

## S2.8 · ros2_control with mock hardware

**Goal:** the full control stack running against a simulated robot, so that the real hardware
interface in S2.11 is the only new variable.

**You will be able to:** explain what the `ros2_control` seam is and name what sits on each side of it, swap the hardware behind a live controller stack by changing one string, and diagnose a controller that loads and then does nothing.

### Concept

`ros2_control` standardises how controllers talk to robot hardware. Controllers — a joint trajectory
controller, say — read state interfaces and write command interfaces. What sits behind those
interfaces is a plugin, loaded at runtime. Swap the plugin and the same controllers drive simulation
or hardware without changing.

> **DEFINITION** — **The four words this session is built out of.** A **state interface** is one named,
> readable number coming *up* from the hardware — `shoulder_joint/position` is a state interface, and
> so is `shoulder_joint/velocity`. A **command interface** is one named, writable number going *down* —
> `shoulder_joint/position` again, but a different object with the same name, which is a genuine
> source of confusion until you notice that the direction is the distinguishing feature. The
> **controller manager** is the process that owns the update loop: it calls your hardware plugin's
> `read()`, then every active controller's `update()`, then `write()`, at a fixed rate you set. A
> **controller** is a plugin that claims some command interfaces, reads some state interfaces, and
> converts a goal into numbers. Nothing in this framework has any idea what a robot is. It moves named
> doubles across a seam at a fixed rate, and every bit of its usefulness comes from that being all it
> does.

```
FIGURE S2.8.1 — The seam, and the one line that moves it

   ┌──────────────────────────────────────────────────────────────┐
   │  MoveIt 2  (S2.13)                                           │
   └───────────────────────────┬──────────────────────────────────┘
                               │ FollowJointTrajectory action
   ┌───────────────────────────▼──────────────────────────────────┐
   │  CONTROLLERS   joint_trajectory_controller                   │
   │                joint_state_broadcaster                       │
   │                gripper_controller        (S2.10)             │
   └───────────────────────────┬──────────────────────────────────┘
     reads state_interfaces    │  writes command_interfaces
   ════════════════════════════╪═════════════════════════════════  ← the seam
   ┌───────────────────────────▼──────────────────────────────────┐
   │  HARDWARE PLUGIN — chosen by ONE <plugin> line in the URDF   │
   │                                                              │
   │   S2.8   mock_components/GenericSystem      (no hardware)    │
   │   S2.7   gz_ros2_control/GazeboSimSystem    (Gazebo)         │
   │   S2.11  mimic_hardware/MimicSystem         (your CAN bus)   │
   │                                                              │
   │   The Gazebo row needs one extra thing: a separate           │
   │   <gazebo><plugin filename="gz_ros2_control-system">         │
   │   block. It is the only row that is not just one line.       │
   └───────────────────────────┬──────────────────────────────────┘
                               │  read()  /  write()
   ┌───────────────────────────▼──────────────────────────────────┐
   │  Gateway MCU ──CAN── Joint 1 · Joint 2   (Stage 1 code)      │
   └──────────────────────────────────────────────────────────────┘

   Everything above the seam is unchanged across all three plugins.
   That is the entire value of the framework, and seeing one line do
   it is worth more than reading about it.
```

### Build

Start with `mock_components/GenericSystem`, which loops commands straight back as state. Get a
`joint_trajectory_controller` moving your simulated arm. Only then write real hardware.

### Draw this

**The seam, in your own words, before you read FIGURE S2.8.1 again.** Two boxes and one line: what is
above, what is below, and what crosses. Then write on the crossing line the *only* two verbs that
cross it — `read()` and `write()` — and on each side, the thing that never crosses: controllers never
touch hardware, and hardware never knows what a controller is.

Underneath, list your three plugin strings and mark which single line in which single file selects
between them. If that drawing takes more than five minutes you have not understood the seam yet, and
five minutes now saves an afternoon in S2.11.

### Code — skeleton, the `<ros2_control>` block

This goes in your URDF (or an xacro included by it). The `<plugin>` line is the only thing that
changes when you swap simulation for real hardware in S2.11 — that is the entire point of the
framework, and seeing one line do it is worth more than reading about it.

```xml
<ros2_control name="MimicArm" type="system">

  <hardware>
    <!-- S2.8: mock. S2.11: swap this ONE line for mimic_hardware/MimicSystem -->
    <plugin>mock_components/GenericSystem</plugin>
    <!-- <plugin>mimic_hardware/MimicSystem</plugin>
         <param name="serial_port">/dev/ttyACM0</param>
         <param name="baud_rate">250000</param>                          -->
  </hardware>

  <joint name="shoulder_joint">
    <command_interface name="position">
      <!-- NOT derived in S2.3 — S2.3 only constrains the ELBOW. These are mechanical
           limits: set them from your CAD once the base and link 1 exist, so the arm
           cannot swing into the plank or its own cabling. ±3.14 is a placeholder. -->
      <param name="min">-3.14</param>
      <param name="max">3.14</param>
    </command_interface>
    <state_interface name="position"/>
    <state_interface name="velocity"/>
  </joint>

  <joint name="elbow_joint">
    <command_interface name="position">
      <!-- 15°..165°, the singularity limits derived in S2.3.
           NOTE: S2.3 allows |θ₂| in that band, i.e. TWO disjoint ranges
           (elbow-up and elbow-down). A single min/max pair cannot express a
           disjoint set, so this commits you to the POSITIVE branch only.
           That is a deliberate choice, not an oversight — see below. -->
      <param name="min">0.262</param>      <!-- 15°  -->
      <param name="max">2.880</param>      <!-- 165° -->
    </command_interface>
    <state_interface name="position"/>
    <state_interface name="velocity"/>
  </joint>

  <!-- Added in S2.10 -->
  <joint name="gripper_joint">
    <command_interface name="position"/>
    <state_interface name="position"/>
  </joint>

</ros2_control>
```

> **WATCH OUT** — **Two things in that block will bite you, and both look like faults when they are
> not.**
>
> **One: the elbow limits foreclose a branch.** S2.3 has you write `15° ≤ |θ₂| ≤ 165°`, which is two
> disjoint ranges — elbow-up *and* elbow-down. URDF and `ros2_control` joint limits are a single
> interval and cannot express that. Committing to the positive branch here is the right call (it is
> the "choose consistently" rule from S2.3, enforced by the model rather than by your solver's good
> behaviour), but it means **your IK must return the positive-θ₂ solution or the controller will
> reject the goal.** Write that in `docs/decisions/` alongside the branch rule, because otherwise it
> reads later as an arbitrary sign.
>
> **Two: `GenericSystem` will report zero velocity.** You have declared a `velocity` state interface
> with no matching velocity command interface. `mock_components/GenericSystem` mirrors commands to
> states, so with nothing to mirror, `velocity` reads **0.0 forever** — and the joint trajectory
> controller below asks for it. Add `<param name="calculate_dynamics">true</param>` inside
> `<hardware>` and the mock will differentiate position for you. Without it, everything runs, nothing
> errors, and every velocity plot you make in simulation is a flat line. That is a much worse failure
> than a crash.

### Code — skeleton, the controller configuration

`config/controllers.yaml`. The controller manager's `update_rate` is a real-time parameter and it is
the ROS 2 equivalent of the `DT_US` you fought over in Stage 0 — same concept, one layer up.

```yaml
controller_manager:
  ros__parameters:
    update_rate: 100          # Hz. Your joints close their own loops at 1 kHz; this
                              # is only the rate targets are handed down at.
    joint_state_broadcaster:
      type: joint_state_broadcaster/JointStateBroadcaster
    arm_controller:
      type: joint_trajectory_controller/JointTrajectoryController
    gripper_controller:                       # added in S2.10
      type: parallel_gripper_action_controller/GripperActionController

arm_controller:
  ros__parameters:
    joints: [shoulder_joint, elbow_joint]
    command_interfaces: [position]
    state_interfaces: [position, velocity]
    # TODO: constraints.goal_time, and per-joint trajectory tolerances.
    #       Decide these deliberately — they are what makes a goal "failed"
    #       rather than "still trying", and that is a safety property.

gripper_controller:
  ros__parameters:
    joint: gripper_joint                      # singular. It is one joint.
    # TODO: max_effort, and the stall timeout that decides "closed on something"
    #       versus "still closing" — this is where isHolding() lands in ROS 2.
```

> **WATCH OUT** — **A joint declared in `<ros2_control>` but claimed by no controller is inert.** It
> shows up in `/joint_states`, it accepts nothing, and it fails silently rather than loudly. The
> gripper controller above is what makes S2.10's `open(fraction)` reachable from ROS 2 instead of
> through a side channel. If you would rather drive it as a plain float, a
> `forward_command_controller/ForwardCommandController` is the simpler substitute, and for a two-DOF
> arm with one gripper joint it is a perfectly defensible choice — see the box below before you
> assume the action controller is the obvious answer.

> **WATCH OUT** — **There are two `GripperActionController`s, the older one is on its way out, and the
> MoveIt story is not as clean as it looks.** Three separate things to get right here.
>
> **One — which controller.** You will find `position_controllers/GripperActionController` in every
> tutorial and most of Stack Overflow. It still loads on Jazzy, and the Jazzy migration notes state it
> is to be removed, with `parallel_gripper_action_controller/GripperActionController` as the
> replacement. Use the new one, as written above. The `joint:` key is singular in both, because it
> really is one joint.
>
> **Two — two plugin strings are in circulation for the replacement.** The Jazzy migration guide and
> the userdoc give `parallel_gripper_action_controller/GripperActionController`, which is what this
> workbook uses; the runtime deprecation message has been seen naming
> `parallel_gripper_controllers/GripperActionController`. Given this workbook's own warning about
> package names versus class names, do not guess: run **`ros2 control list_controller_types`** on the
> machine you are actually on and copy the string it prints.
>
> **Three — do not assume MoveIt can drive it.** The new controller uses the
> `control_msgs/ParallelGripperCommand` action, and MoveIt's `MoveItSimpleControllerManager` has not
> historically supported that action type — using it produced an error, and it is a known, tracked
> MoveIt issue. That may or may not be resolved in the MoveIt build you install. **Verify it before
> S2.13 depends on it**: check `moveit_controllers.yaml`'s supported action types against
> `ros2 action list` once both are running. If it is not supported, `ForwardCommandController` plus
> your own thin action wrapper is the fallback, and it is a smaller problem found early than late.
>
> This is the *same* situation as the deprecated `export_*_interfaces()` methods flagged in S2.11, and
> it is worth noticing that it happened twice in one stage. The habit to build is not "memorise these
> two"; it is **check `control.ros.org` for the distribution you are actually on before you copy any
> controller type string**, because the tutorials lag the API by roughly one release.

> **LOOK THIS UP** — Watch **Articulated Robotics**' `ros2_control` series before you start this session.
> It is the clearest available walkthrough of the controller-manager / hardware-interface split, and
> it shows the bring-up sequence rather than just the YAML. Watch it *after* you have read
> FIGURE S2.8.1 and can say in your own words what the seam is, so you are checking your model rather
> than acquiring one.

### Code — skeleton, the launch file

`launch/arm.launch.py`. You need this three times over (mock, Gazebo, real), so write it once with a
`use_mock` argument rather than copying it.

```python
# TODO:
#  - DeclareLaunchArgument('use_mock', default_value='true')
#  - robot_description   := xacro of your URDF, with use_mock passed in
#  - Node: robot_state_publisher      <- takes robot_description
#  - Node: controller_manager (ros2_control_node)
#  - Node: spawner joint_state_broadcaster
#  - Node: spawner arm_controller     <- AFTER the broadcaster; order matters
#  - Node: spawner gripper_controller <- also after the broadcaster (S2.10)
#  - Node: rviz2, with your saved config, on a condition
```

> **WATCH OUT** — Spawn `joint_state_broadcaster` **before** your arm controller. If the broadcaster is
> not up, rviz2 shows a robot frozen at the origin and every joint reads zero, which looks exactly
> like a hardware fault and is not one. This is the single most common ros2_control bring-up
> confusion and it costs people an evening.

### What will go wrong

- **The spawner times out.** `Controller manager not available` means the spawner started before
  `ros2_control_node` was ready. `ros2 control list_controllers` is the diagnostic — if it errors, the
  manager is not up; if it lists your controller as `unconfigured`, the manager is fine and your YAML
  is not being found. Check the parameter file path in the launch file before you suspect anything
  else.
- **`Controller ... failed to load` with a pluginlib error.** The type string in `controllers.yaml`
  does not match a registered plugin. These strings are `package_name/ClassName` and are
  case-sensitive; pasting a package name where a class name belongs is the usual cause and it is why
  FIGURE S2.8.1 spells all three out in full.
- **The controller loads, activates, and nothing moves.** It has not claimed the interfaces you think.
  `ros2 control list_hardware_interfaces` shows every interface and who claims it. An unclaimed
  command interface is the single most useful thing that listing tells you.
- **Every velocity in your plots is exactly zero.** `calculate_dynamics` is not set on the mock. See
  the warning above — this one produces no error at all and invalidates every simulated tuning run you
  do until you catch it.
- **Two controllers both want the same command interface.** The second one refuses to activate. Only
  one thing may write a given interface at a time, which is the framework preventing a real class of
  bug rather than being awkward.

**Capture the broken state.** The velocity plot that is exactly zero everywhere, because
`calculate_dynamics` is unset on the mock. Save it. **This failure produces no error of any kind** —
everything loads, everything activates, every controller reports healthy — and a flat line where a
velocity should be is the only evidence it ever existed.

### Prove it

1. `ros2 control list_hardware_interfaces` lists every interface you declared, and shows the command
   interfaces as **claimed** by your controller.
2. `ros2 control list_controllers` shows both the broadcaster and the arm controller **active**.
3. A trajectory goal moves the mock arm, and `/joint_states` reports it moving.
4. **Velocity is not zero.** Plot it. This is the check that catches `calculate_dynamics`, it produces
   no error of any kind, and skipping it invalidates every simulated tuning run you make afterwards.

> **CHECK YOURSELF** — Before you leave: `shoulder_joint/position` exists twice in that interface
> listing, once as a state and once as a command. Say what makes them different objects, and which one
> your controller writes. If that still feels like a trick, re-read the four-words definition above —
> it is the distinction the whole framework is built on.

> **CHECK YOURSELF** — Then swap the `<plugin>` line to a deliberately wrong
> string and watch it fail, then swap it back. Knowing what the failure *looks like* is what makes
> S2.11 an afternoon instead of a weekend — you will be changing exactly this line, on hardware, with
> more variables in play.

### Artifacts

- **`docs/sessions/ros2-control/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `config/controllers.yaml` and `launch/arm.launch.py`, committed, with the `use_mock` argument.
- The controller type strings you actually verified with `ros2 control list_controller_types`, in
  `docs/decisions/`, with the date — because they move between releases.
- **Site:** one paragraph, no picture needed. "The same controllers drive mock hardware, Gazebo and my
  own CAN bus, and swapping between them is one line in a URDF." That sentence is the whole value of
  the framework and most people who list `ros2_control` cannot say it.
  **The shot:** the paragraph, plus **one screenshot that earns it**: `ros2 control
  list_hardware_interfaces` with your command interfaces showing as *claimed*. That listing is the
  seam made visible, it is a still of readable text, and it is the evidence for a sentence that
  otherwise has to be taken on trust.

---

# PART III — HARDWARE

---

## S2.9 · Print and assemble

**Goal:** a physical arm on a rigid base.

**You will be able to:** size a printed fit from a measured coupon rather than from a nominal dimension, and state your machine's actual dimensional error as a number.

### Concept

Twenty hours is budgeted here and almost none of it is your hands. It is print time, and the loop is
design → print → discover a tolerance is wrong → redesign → reprint, two or three times per part. The
only lever you have on the total is **how many iterations each part needs**, and the way to reduce
that is to print small test coupons rather than whole links: a 20 mm block with your bearing seat, your
insert boss and your screw clearance in it takes twenty minutes and tells you everything a six-hour
link would.

Run firmware and simulation work while the printer runs. A stage where the bottleneck is a machine is
a stage where you should be doing something else with your hands.

### Build

1. **Print the tolerance coupon first.** Bearing seat, M3 insert boss, M3 clearance hole, and a
   sliding fit. Measure all four with the calipers. **Write the four deltas into
   a print-tolerances ADR in `docs/decisions/` the moment you have measured them**, with the filament,
   the nozzle and the layer height beside them, and apply them to every subsequent part. Those four
   numbers are a property of *your* machine with *that* material, they are the difference between one
   reprint and three, and they are only true until you change filament.
2. **Print the joint housings before the links.** They carry every fit that matters; the links are
   just beams.
3. **Heat-set inserts everywhere a screw enters plastic.** Same technique and same tip as the Stage 0
   motor mount.
4. **Dry-assemble the whole arm before threadlocker.** Check the range of motion by hand against the
   URDF limits, and check that no cable is stretched at either end of travel.
5. **Then threadlocker on every fastener that will see vibration** — a two-DOF arm vibrates more than
   you expect, and a fastener backing out mid-motion is both a failure and a hazard.
6. **Weigh every part as it comes off the printer**, and put the real masses into S2.4.
7. **Measure the backlash in each joint**, because it is defined in three documents and measured in
   none — and it is the number that explains half of what your controller does later.

### The math — measuring backlash, which costs ten minutes

**Backlash** is the free play in a gear train: the angle you can turn the output before the input
starts to move. Your encoder is on the *motor* side of the gearbox, so it is structurally blind to it —
the motor turns, the encoder counts, and the link has not moved yet.

Measure it directly, with power off and the arm horizontal:

```
   1. Drive the joint to a target from BELOW — approach it moving up — and
      record the encoder count and the physical tip position.
   2. Drive to the SAME target from ABOVE.
   3. The difference between the two tip positions is the backlash, referred
      to the output. Convert it to degrees at the joint:
            backlash [deg] = atan(Δtip / L) × 180/π

   Repeat at three points across the range, because it is rarely uniform —
   gear trains have tight spots.
```

Expect somewhere between a few tenths of a degree and a couple of degrees on a hobby gearbox. Write the
number in `docs/tuning/`, and then use it, because it explains three things you will otherwise
misdiagnose:

- **Your repeatability has a floor** — approaching a target from one direction is repeatable, from
  either direction is not, and the spread is roughly the backlash. S2.12's homing spread is measured
  the same way for the same reason.
- **The chatter at rest in S8 is real** and now has a size. If your measured backlash is 1° and your
  encoder resolves 0.03°, the controller can hunt across thirty counts of nothing.
- **It is a good argument for the AS5600.** An absolute encoder on the *joint axis* sees past the
  gearbox and measures where the link actually is. That is the thing the motor encoder structurally
  cannot do, and now you have the number that says how much it is worth.

> **CHECK YOURSELF** — Before you measure: predict whether backlash makes your step response look
> *better* or *worse*, and what it does to overshoot specifically. There is a defensible argument in
> both directions and thinking it through is worth more than the number.

Expect to reprint at least one part because of a tolerance you got wrong. This is normal, it is why
the printer beats an outsourced service for iteration, and it is why steps 1 and 2 are ordered as they
are — a coupon costs twenty minutes and a link costs six hours.

> **WATCH OUT** — **Fit the emergency stop before the first powered test of the assembled arm, not after
> the first incident.** Wire it to cut *motor* power, not logic power, so the system survives to
> report what happened. A multi-joint arm with a sign error moves fast, in an unexpected direction,
> with real torque.

### Draw this

**Nothing, and this is the session where that is most obviously right.** Twenty hours of print time
and assembly produces measurements and parts, not diagrams — the coupon's four measured deltas and
the backlash figure are the artifacts, and both are numbers. A drawing here would be a drawing of
something you are holding.

The one exception, if a joint fights you: sketch the cable route at both ends of travel. Nine times
out of ten a joint that binds at one end and not the other is a cable, and the drawing that finds it
takes two minutes.

### What will go wrong

- **The bearing does not fit, either way.** Printers over-extrude, so holes come out undersized and
  posts oversized. This is what the coupon is for; do not size a joint housing by guessing twice.
- **A heat-set insert sinks in crooked, or too deep.** Go in slower and colder than feels right, and
  keep the iron perpendicular. An insert that ends up below the surface still holds; one that ends up
  at an angle cracks the boss on the first fastener.
- **A link snaps at a layer line under load.** Print orientation. Reorient so the load runs along the
  layers, add walls rather than infill, and reprint.
- **The arm is heavier than S2.4 assumed.** Extremely likely, because the budget excluded fasteners,
  inserts, bearings and cable. This is not a failure; it is the reason exit criterion 10 asks for
  measured masses. Re-run the torque page.
- **A joint binds at one end of travel and not the other.** Cable, nine times out of ten. Check it
  before you suspect the mechanism.

**Capture the broken state.** **Keep the parts, not just the photographs.** The tolerance coupon
whose bearing seat came out undersized, the insert that went in crooked, and above all the link that
snapped along its layer lines. Photograph the break face on that one — the layer lines are visible
in the fracture and they are the argument for print orientation being a structural decision. A box
of failed prints costs nothing to keep and cannot be recreated on purpose.

### Prove it

> **CHECK YOURSELF** — Before you weigh anything: predict the total mass of the printed parts from your
> CAD figures, then weigh them. CAD models a solid; you printed walls and infill. Which direction will
> the error go, and roughly how far? Getting the *direction* right matters more than the magnitude, and
> it tells you whether you understood what the slicer did.

Back-drive both joints by hand through their full range with the power off. Nothing should bind,
click, or need force that varies with position. Then, with motor power still disconnected, verify the
e-stop actually breaks the motor rail with a meter — a stop you have not metered is a stop you are
assuming.

### Artifacts

- **`docs/sessions/print-and-assemble/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- The print-tolerances ADR in `docs/decisions/` — your machine's four measured deltas.
- **Measured mass of every printed part**, and the re-run S2.4 budget.
- Photograph of the assembled arm next to the Gazebo render of the same pose.
- **Site:** that photograph. The same arm, simulated and real, in the same pose, side by side — it
  needs no caption and it is the single most legible image Stage 2 produces.
  **The shot:** one still, both arms in the same pose, same camera angle, same crop — the render
  and the photograph placed as a pair. Shoot the real one against a plain background; the point is
  the correspondence, and a cluttered bench breaks it.

---

## S2.10 · The gripper — the end effector everything downstream assumes

**Goal:** a working two-finger gripper on the end of link 2 that opens and closes on command, reports
whether it actually closed on something, and whose real mass goes back into S2.4.

**You will be able to:** size an actuator from a required grasp margin rather than from a derate you guessed, and explain why an open-loop servo cannot tell you whether it gripped anything and what three things you could do about it.

### Concept

Up to now the gripper has been a mass in a torque budget and a frame called `gripper_tip` in your
URDF. It has to become a real thing here, because **every stage after this one depends on it**:
Stage 3's pick-and-place has nothing to pick with, and Stage 4's whole payoff is opening and closing
this gripper from your own forearm muscles.

It is also the one part of the arm where "good enough" genuinely is good enough. A two-finger
parallel or pivoting gripper made of printed links and an SG90 is a solved problem with a hundred
open designs to learn from. **Do not spend three weeks here.** Spend one session, get something that
grips, and move on — but get the interface right, because the interface is what Stages 3 and 4 talk
to.

### The math — will an SG90 actually close it?

You own an SG90 from the starter kit. Check it rather than assuming it, the same way you checked the
arm motors:

```
FIGURE S2.10.1 — Where grip force comes from

   ONE finger is drawn. There are TWO, and the friction sum below counts
   both — that factor of 2 doubles your margin and it is easy to lose.

           servo shaft axis                   finger
                 ●──────────────────────────────────┐
                ╱ ╲                                 │   ← TPU pad
         τ ↻   │ + │                                ▓ ═════ object, 100 g
                ╲ ╱                                 │   ← TPU pad
                 ●──────────────────────────────────┘
                 │◄────────── r = 40 mm ───────────►│
                                                    │
                                               F = τ / r   per finger

   r is measured from the SERVO SHAFT AXIS to the contact point, not from
   the end of the horn. That is the distance F = τ/r divides by, so a
   longer finger buys reach and spends force in exact proportion.

   τ  = 1.8 kg·cm at 4.8 V  =  0.177 N·m       (stall — a limit, not
   F  = 0.177 / 0.040       =  4.4 N            an operating point)
   design at 30 % of stall  =  1.3 N per finger  ← a CHOSEN derate,
                                                   see the note below

   THEN THE FRICTION SUM — this is the part people skip:

        holding force = 2 · µ · F      (two fingers, each pressing F)
                      = 2 · 0.5 · 1.3  = 1.30 N
        weight        = 0.100 · 9.81   = 0.981 N
                                          ─────────
        safety factor = 1.30 / 0.981   = 1.33×    ← MARGINAL

   Longer finger  → more reach, less force  (F = τ/r)
   Higher µ (TPU) → more force for free     (µ ≈ 1.0 gives 2.65×)
   A lip or V     → carries load mechanically, costs only CAD
```

Those five lines in the figure are the whole calculation; the paragraphs below take them apart.

> **WATCH OUT** — **Where 30 % comes from, stated honestly.** It is a derate you are choosing, not a
> standard you are following — the same category of number as S2.4's 25 %-of-stall rule, and it
> deserves the same treatment. The *reason* to derate at all is real: a hobby servo held against a
> stop draws stall current continuously, and an SG90 held there cooks its driver chip and strips its
> nylon gear train in minutes. But 30 % specifically is a convention, and you should be able to say so.
>
> **The better move is to run the calculation backwards**, because then the derate stops being an
> assumption and becomes a *result*. Decide the safety factor you want on the grasp, and solve for the
> torque that delivers it — the arithmetic is immediately below this box.

```
required force per finger   F  =  SF × weight / (2 · µ)
required torque             τ  =  F × r

at µ = 0.5, r = 40 mm, a 100 g object (0.981 N):
    SF = 1.5×  →  F = 1.47 N  →  τ = 0.059 N·m  =  33 % of stall
    SF = 2.0×  →  F = 1.96 N  →  τ = 0.079 N·m  =  44 % of stall
    SF = 3.0×  →  F = 2.94 N  →  τ = 0.118 N·m  =  67 % of stall
```

> **WATCH OUT, continued** — So 30 % of stall and a 1.33× grasp margin are **the same number seen from
> two ends**, and the honest sentence is not "I derated to 30 %" but "I designed for a 1.33× friction
> margin, which needs 30 % of the servo's stall torque, and here is why 1.33× is not enough." Pick the
> margin first. The derate falls out of it.

**Now do the friction sum, because "1.3 N sounds like enough" is not an answer.** A friction grasp
holds when the friction the pads can generate exceeds the object's weight:

```
Weight of a 100 g object      =  0.100 × 9.81            =  0.981 N
Friction available, two fingers, µ ≈ 0.5:
      2 × µ × N  =  2 × 0.5 × 1.3                        =  1.30 N

Safety factor = 1.30 / 0.981 = 1.33×
```

> **WATCH OUT** — **1.33× is marginal, not adequate, and you should say so rather than round it up.**
> Friction grasps are normally designed to 2–4×, and this figure is *static* — it is the margin for an
> object hanging motionless. The arm accelerating upward at about 0.33 g eats all of it, and Stage 3
> moves. Three things buy the margin back, in order of cheapness:
>
> 1. **TPU pads.** µ for TPU on a printed PETG block is typically 0.8–1.2, not 0.5. At µ = 1.0 the
>    margin is 2.65× and the problem goes away. **This is why S2.5 specified TPU** — on a printed
>    gripper, *grip comes from the surface, not from the servo.* But it is an assumption until you
>    measure it, and 0.5 is the conservative number to design against.
> 2. **A shorter finger.** Grip force is `τ / r`. At a 30 mm lever instead of 40 mm you get 5.9 N at
>    stall and 1.8 N at 30 %, for a 1.8× static margin at µ = 0.5. A longer finger multiplies reach
>    and divides force; pick deliberately.
> 3. **Form closure.** A shallow V or a lip in the finger geometry carries load mechanically instead
>    of by friction, and costs nothing but CAD.
>
> **Measure µ before you trust it:** rest the printed block on a TPU pad, tilt until it slides, and
> `µ = tan θ`. Ten minutes, and it converts one of the two weak assumptions here into a number.

> **WATCH OUT** — **The 1.8 kg·cm figure is the single least reliable number in this workbook, and the
> margin is directly proportional to it.** It is quoted universally and there is no manufacturer
> datasheet behind it — "SG90" is a form factor sold by dozens of factories, and measured clones
> commonly deliver 1.2–1.5 kg·cm rather than 1.8. Because grip force is linear in torque, so is your
> margin — the table is immediately below this box.

```
  stall 1.8 kg·cm  →  1.33×    the figure above
  stall 1.5 kg·cm  →  1.10×
  stall 1.4 kg·cm  →  1.03×    effectively zero margin
  stall 1.2 kg·cm  →  0.88×    it drops the object
```

> **WATCH OUT, continued** — A 22 % shortfall on a number you cannot verify is the difference between
> marginal and not working.
> **Measure the servo, do not read it** — hang a known mass from the horn at a known radius and find
> where it stalls, which is the same forensics you did on the N20 in Stage 0 S1. Then design from your
> measurement. If it comes in low, the fix is cheap and already listed above: shorter fingers, TPU
> pads, or a lip. The expensive version is discovering it during Stage 3's pick-and-place, where a
> dropped block looks like a vision error.

Redo all of the above with *your* lever arm and *your* measured µ, and put the result in the ADR.

> **WATCH OUT** — **The SG90 is 9 g, and S2.4 assumed an 80 g "gripper assembly."** That 80 g is the servo
> *plus* fingers, linkage, fasteners and mount — which is realistic, but it is an assumption. **Weigh
> the finished gripper and put the real number back into the S2.4 budget.** If it comes out at 120 g,
> that is 40 g extra at the tip: `0.040 × 9.81 × 0.360 = 0.141 N·m` more at the **shoulder** and
> `0.040 × 9.81 × 0.180 = 0.071 N·m` more at the **elbow**. Know which joint you are quoting — they
> differ by exactly the factor of two between the two lever arms, and that is an easy sentence to get
> wrong.

### Build

1. **Pick a mechanism and write down why**, in `docs/decisions/`. Two-finger parallel
   (jaws stay parallel, better on flat objects, needs a linkage) or pivoting/scissor (simpler, fewer
   parts, contact angle changes as it closes). Either is fine for blocks with fiducial markers on
   them; say which you chose. The same file takes the grip-force arithmetic with your measured servo
   torque and your measured µ, and the feedback method from the table further down — they are three
   parts of one decision about the same mechanism and splitting them across three files loses the
   argument.
2. **Print fingers in PETG, pads in TPU.** Heat-set inserts wherever a screw enters plastic.
3. **Mount the servo to link 2, not to the fingers — and know what that costs you mechanically.**
   A servo bolted to the finger drives it directly; a servo bolted to link 2 has to get motion across
   a distance, which means a linkage, and the linkage is the actual mechanical difficulty of this
   session. Three ways to bridge it, cheapest first:

   - **Direct, on a short mount.** Put the servo as close to the jaws as the geometry allows and drive
     one finger straight off the horn, with the second finger geared or linked to mirror it. Simplest,
     and it is only "mounted to link 2" in a loose sense — the mass is still fairly far out.
   - **A pushrod.** One rigid rod from the horn to a pivot on the finger, exactly like an RC control
     surface. Two ball joints or two loose pin joints, and it tolerates being slightly wrong. This is
     the one to build first.
   - **A four-bar per finger**, which is what makes jaws stay *parallel* as they close. More parts,
     better on flat objects, and considerably more CAD.

   Whichever you pick, the servo's rotation and the finger's rotation are no longer the same angle, so
   **`r` in `F = τ/r` is the lever at the *finger pivot*, not at the servo horn** — the linkage ratio
   sits between them. If your linkage is 1:1 the arithmetic above stands unchanged; if it is not,
   multiply it through, and this is the third time this stage has asked you to multiply an option
   through before believing it.

   Mass at the tip is the most expensive mass on the arm. The tip sits `L₁ + L₂ = 0.360 m` from the shoulder, so every **gram** there costs
   `0.001 × 9.81 × 0.360 ≈ 0.0035 N·m` at the shoulder — about 3.5 mN·m per gram, or 0.35 N·m per
   100 g. Ten grams saved at the fingers is worth thirty at the shoulder bracket.
4. **Wire the servo signal to a spare pin on the joint-2 controller**, or to the gateway MCU. Servo
   power comes off the **5 V logic rail, not the 12 V motor rail**, and it needs its own bulk
   capacitor: an SG90 stalling browns out a shared 5 V rail exactly the way the drive motors did in
   Stage 0 S2. This is the same lesson, in a smaller package.
5. **Add it to the URDF** as a joint of type `prismatic` (parallel jaws) or `revolute` (pivoting),
   with limits, plus a `<ros2_control>` `command_interface` so it is driven the same way as
   everything else rather than through a side channel.

### Draw this

**Your linkage, as a mechanism, with the two levers marked.** Servo horn at one end, finger pivot at
the other, and the rod or gear between them. Then mark **two** radii: the horn radius the servo torque
acts at, and the finger radius the grip force acts at. The ratio between them is your linkage ratio and
it multiplies straight into `F = τ/r` — which is why the figure's arithmetic only holds unchanged at
1:1.

Then draw the jaws closed on a 40 mm block and closed on a 10 mm block, and check the contact angle in
both. A pivoting gripper's fingers are not parallel, so the force direction changes with opening — and
if the contact normal points outward at small openings, the object squirts out rather than being held.
That is a five-minute drawing and a reprint you do not do.

### The interface — the part that actually matters

Stage 3 will issue "grasp" and "release". Stage 4 will issue a continuous opening from an EMG
envelope. Design for both **now**:

```
open(fraction)      // 0.0 = fully closed, 1.0 = fully open. Continuous, not binary.
isHolding() -> bool // did it stop short of fully closed? Then something is in it.
```

`isHolding()` is the whole session in one function, and it is harder than it looks. **A stock SG90
reports nothing** — it takes a pulse width in and gives you no position, no current, no torque. You
cannot infer "it stopped early" by comparing commanded position against expected position, because
you never learn the actual position. That is a real dead end and it is worth understanding *why*
before you pick a way around it.

Three that work, cheapest first:

| Method | How | Cost | Catch |
|---|---|---|---|
| **Microswitch in the jaw** | Switch closes when the fingers reach the fully-closed stop. Closed *and* switch pressed = empty; closed *and* switch open = holding something. | **C$0 — you own ten** | Binary. Tells you *that* something is there, not how big. |
| **Current sensing** | An SG90 pushing against an object draws far more than one sitting at its target. Sense the servo's 5 V feed with one of your three INA219s and threshold it. | C$0 — you own three | Needs a calibration pass, and the current spikes during *every* move, so you must sample after motion settles. |
| **Potentiometer tap** | Solder a wire to the servo's internal pot wiper and read it on an ADC. Now you have real position feedback and the "stopped short" inference becomes valid. | C$0 + a modification | Voids the servo, and it is fiddly. Do this only if you want the position for its own sake. |

**Start with the microswitch.** It is the one you can build tonight, and Stage 3 only needs the
boolean. Write down which you chose and why — an interviewer asking "how did you know it had
gripped?" is asking whether you noticed that an open-loop actuator cannot answer the question.

**A gripper that cannot tell you whether it grabbed anything makes Stage 3's failure handling
impossible**, and Volume VI's M3.4 explicitly asks what happens "when the gripper closes and feels
nothing."

### What will go wrong

- **The servo buzzes continuously when closed.** It is fighting to reach a position it cannot reach.
  Back the closed limit off, or detach/de-energise the signal once closed.
- **The arm droops when the gripper closes.** Rail sag, or you just added mass at the tip and did not
  update S2.4.
- **Fingers splay under load.** Printed layer lines running across the load path. Reorient and reprint.

**Capture the broken state.** The gripper dropping the object. Film one drop. Ten successful grasps
prove the margin is adequate; one drop, next to your computed 1.33× safety factor, proves you knew
it was marginal before it happened — and being able to say that is worth considerably more than ten
out of ten.

### Prove it

> **CHECK YOURSELF** — Before the first grasp: you measured your servo's real stall torque and your
> pads' real µ. Put both into the friction sum and predict your actual safety factor. Then predict how
> many of ten grasps will hold. If your predicted margin is under about 1.5× and all ten hold anyway,
> work out which of your two measurements was pessimistic — that is a more useful result than ten
> successes.

Pick up and hold a 100 g object, ten times out of ten, from the same commanded pose. Then release it
ten times. Then weigh the gripper and update S2.4.

### Artifacts

- **`docs/sessions/gripper/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- The gripper ADR in `docs/decisions/` — mechanism chosen, alternatives, the grip-force arithmetic.
- **Updated `docs/derivations/torque-budget.jpg`** with the measured gripper mass replacing the
  assumed 80 g.
- **Site:** a short video of it picking up and holding something. It is the first moment the arm looks
  like it has a purpose.
  **The shot:** one clip, 15 to 20 seconds, one take: approach, close, lift, hold for a beat,
  place. **The object and both jaws in frame throughout.** Do not cut the lift — the held moment
  in the middle is the whole thing.

---

## S2.11 · The hardware interface — where the two layers meet

**Goal:** a `SystemInterface` plugin whose `read()` pulls joint states off your CAN bus and whose
`write()` pushes targets out.

**You will be able to:** explain where a real-time control loop ends and a soft-real-time host begins, and say why `read()` and `write()` must not block — the third time this project makes that argument and the first time you feel it.

### Concept

This is the seam. Everything below it is your Stage 1 firmware; everything above is ROS 2. It is
where eight months of separate work finally connect, and it is deliberately a thin adapter — because
your `Joint` class already exposes exactly the state that the interface needs.

### The architecture — bridge first, micro-ROS later

```
Host (ROS 2) ──USB serial── Gateway MCU ──CAN── Joint 1
                                            └── Joint 2
```

Start with a **plain serial bridge** to one gateway microcontroller that speaks CAN to the joints. You
control every byte, you can debug it with a terminal, and nothing is hidden. Migrate to **micro-ROS**
later if you want the joints to be ROS 2 nodes themselves — and doing it in that order means you will
understand exactly what micro-ROS is doing for you.

### The gateway, and where it comes from

**This is the one new physical node in Stage 2, and you already own it.** It appears in the diagram
above as though it had always been there, so be clear about what it is before you go looking for a
part you did not buy.

The gateway is a third node on the CAN bus whose only job is translation: USB serial on one side, CAN
on the other, and no control logic at all. It does not close a loop, it does not hold a target, and it
must not be tempted into either — every bit of intelligence stays either in the joints below it or in
`ros2_control` above it. **It is a wire with a protocol converter in the middle**, and keeping it that
dumb is what makes it easy to debug.

**The hardware is the S1.6 bus monitor, promoted.** In Stage 1 you built an ESP32-S3 plus an
SN65HVD230 transceiver to watch frames on the wire. That is exactly a gateway with the USB side
unused — so the gateway costs you nothing new: one ESP32-S3 (you own two), one transceiver (you bought
four), and USB-C to the host.

Three consequences worth planning for rather than discovering:

- **Your ESP32-S3 allocation just got tighter.** Two boards, and now three jobs: bus monitor, gateway,
  and joints three and four later. The gateway is permanently occupied once Stage 2 runs, so watching
  the bus *while the arm is live* needs the third board — about C$12, and Tier F of *What's Left to
  Buy* works the allocation out. Not a problem today; worth knowing before the evening you want to
  debug an arm and monitor the bus at once.
- **A second Nucleo is the alternative** if you bought one as the optional Tier C line, and it is the
  better choice if you would rather not have a second toolchain in play. Either works. Pick one, and
  write a gateway-hardware ADR in `docs/decisions/` saying which and why — this is a real decision with
  a real trade-off, and it costs you a spare board either way, which is the consequence to record.
  Its companion is a gateway-transport ADR: serial bridge now or micro-ROS now,
  and the reason for that order. Write the second one **before** you build the bridge, while the
  choice is still open — afterwards it reads as a description of what you did.
- **Termination moves.** The gateway is now a node on the bus, and if it sits at one physical end it
  needs the 120 Ω and something else loses it. Power off, meter across CANH–CANL, expect ~60 Ω — the
  same check as S1.6, and the reason S1.9 told you to do it *every time you add a node*. This is that
  time.

**What the gateway firmware has to do**, and nothing else:

```
  read a framed command from USB serial
    → validate it (length, checksum, known message type)
    → build the CAN frame with the right identifier
    → transmit

  receive a CAN state or diagnostic frame
    → pack it into the same serial framing
    → write to USB

  and one more thing that is not translation and belongs here anyway:
    → if the HOST goes silent, stop forwarding commands.
      The joints already fail safe on their own timeout (S1.8), so this
      is belt and braces — but it means a wedged gateway cannot sit there
      replaying the last thing it heard.
```

Note what is *not* in that list: no PID, no interpolation, no unit conversion, no state. If you find
yourself adding any of them, the layering has slipped and the thing you are building is a third control
layer nobody designed.

> **CHECK YOURSELF** — Before you write a line of it: why does the gateway not simply become a ROS 2
> node itself with micro-ROS, and skip the serial framing entirely? There is a good answer and it is
> not "micro-ROS is bad." Write yours down, then read the paragraph above about doing it in that order.

> **WATCH OUT** — micro-ROS is not developed to any safety or medical standard. Entirely appropriate for
> learning and prototyping, entirely inappropriate for anything that touches a patient. Keeping that
> distinction crisp is the kind of judgement the medical device world screens for, and it belongs in
> your README.

### The class

A hardware component extends `hardware_interface::SystemInterface`. You need a no-argument
constructor plus the lifecycle methods `on_configure`, `on_cleanup`, `on_shutdown`, `on_activate`,
`on_deactivate` and `on_error`, and you override `on_init`, `export_state_interfaces`,
`export_command_interfaces`, `read()` and `write()`.

> **WATCH OUT — read this before you type the skeleton below, not after.**
> **`export_state_interfaces()` and `export_command_interfaces()` are deprecated on the Jazzy branch,
> and the skeleton below uses them deliberately.** The framework has moved to creating the interfaces
> itself from the `<ros2_control>` XML block you wrote in S2.8, exposed through
> `on_export_state_interfaces()` / `on_export_command_interfaces()`. Handle access has moved too, from
> direct member access to `get_optional()` and `set_value()`.
>
> The old form still compiles — with warnings, and the warnings are noisy enough that upstream has had
> to suppress them — which is why it is written out here: **it is the version every tutorial, book and
> Stack Overflow answer you find will use**, and recognising it matters. The concrete migration is in
> the Jazzy docs under *Migration Guides → Humble to Jazzy*: delete the two `export_*_interfaces()`
> overrides, and replace direct handle access with `get_optional()` / `set_value()`, both of which
> return a value you are expected to **check** — they can fail when the framework is running
> asynchronous components.
>
> **And expect it to move again.** The interface has changed shape in each of the last few releases
> and there are already further changes queued for the release after Jazzy; the specific replacement
> names are not worth memorising and are not quoted here, because they are exactly the kind of detail
> that will have moved by the time you arrive. So the instruction is not "write what this box says."
> It is **check `control.ros.org` for the distribution you are on, when you reach this session, and
> write the current form.** Then say so in your README. "The API I was being taught was deprecated, so
> I checked the docs and wrote the current one" is a small thing that says a great deal about how you
> work.

```cpp
// mimic_hardware/include/mimic_hardware/mimic_system.hpp  — skeleton
//
// NOTE: export_state_interfaces() / export_command_interfaces() below are
// DEPRECATED on Jazzy. They are written out because every tutorial uses them.
// See the WATCH OUT immediately above before you copy this.
#pragma once
#include "hardware_interface/system_interface.hpp"

namespace mimic_hardware {

class MimicSystem : public hardware_interface::SystemInterface {
public:
  MimicSystem() = default;

  CallbackReturn on_init(const hardware_interface::HardwareInfo & info) override;
  CallbackReturn on_configure(const rclcpp_lifecycle::State & prev) override;
  CallbackReturn on_activate(const rclcpp_lifecycle::State & prev) override;
  CallbackReturn on_deactivate(const rclcpp_lifecycle::State & prev) override;

  std::vector<hardware_interface::StateInterface>   export_state_interfaces() override;
  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

  // TODO: read()  — pull latest MSG_STATE frames, fill pos_[] and vel_[]
  // TODO: write() — serialise commands_[] into MSG_COMMAND frames, push to the gateway
  hardware_interface::return_type read (const rclcpp::Time &, const rclcpp::Duration &) override;
  hardware_interface::return_type write(const rclcpp::Time &, const rclcpp::Duration &) override;

private:
  std::vector<double> pos_, vel_, commands_;
  // TODO: gateway transport handle
};

}  // namespace mimic_hardware
```

Plus a `pluginlib` XML export, `hardware_interface` / `pluginlib` / `rclcpp` / `rclcpp_lifecycle` in
`package.xml`, and a `<plugin>` tag in the URDF's `<ros2_control>` block.

### The order to build it in, because this session has the most moving parts of any in the project

This is where Stage 1's firmware and Stage 2's ROS 2 stack meet for the first time. **Bring them
together one layer at a time, and keep a working configuration you can fall back to at every step.**

1. **Gateway firmware first, tested with a terminal.** Before any ROS 2 is involved, make the gateway
   MCU answer a hand-typed command over serial and print joint state back. If you cannot drive the arm
   from `screen` or `minicom`, nothing above will work and you will be debugging two layers at once.
2. **Then the plugin, against the terminal protocol.** Write `on_init`, `read()` and `write()`.
   Load it with the *same* launch file as S2.8 and the same controllers, changing only the `<plugin>`
   line — that is the whole promise of the framework and this is the moment it either pays off or
   reveals that something above the seam was tangled with the mock.
3. **Then one joint, then two.** Command the shoulder alone with the elbow unpowered. Confirm the
   direction, then the scaling, then add the second joint.
4. **Only then MoveIt.** S2.13 is a separate session for a reason.

### The math — the two rates, and the one that must not be missed

There are now two loops and they are not the same loop:

```
Joint firmware (Stage 1)        1 kHz   closes the position loop
Controller manager (S2.8)        100 Hz  hands targets down
```

The controller manager does **not** close a loop around your motor. It hands down a target every
10 ms and reads back state. Your joint's own 1 kHz loop does the real work. That split is the entire
architecture, and it means a dropped or late frame on the CAN bus is not a control failure — the joint
keeps holding its last target — which is exactly the fail-safe you built in S1.8.

**Budget the round trip before you build it.** At 100 Hz the manager needs a command out and a state
back for every joint within 10 ms, through USB serial, the gateway, and CAN. From S1.6 a frame is
270 µs; four joints of command and state is eight frames, or 2.2 ms of bus time, which fits. The part
that does not automatically fit is the USB serial hop, and that is why `read()` and `write()` must not
block.

### Draw this

**The whole seam on one page, with the rates on it.** This is the drawing that makes the architecture
explicable in an interview, and you can only make it now that every piece exists.

Draw four boxes stacked: host with `ros2_control`, gateway, CAN bus, joint. Between each pair, write
**two** things — the transport (USB serial, CAN at 500 kbit/s, the joint's own internal loop) and the
**rate** (100 Hz down from the controller manager, 100 Hz state back, 1 kHz inside the joint).

Then mark three things that are the actual content of the drawing:

1. **Where the loop is closed.** Put a circle around the joint's own position loop. Nothing above that
   circle closes a loop around your motor, and being able to point at it is the difference between
   describing this system and understanding it.
2. **What happens if each arrow is cut.** Cut the USB link — the joint holds, from S1.8. Cut the CAN
   frame — same. Cut the encoder — nothing saves you. One of those three is not like the others and
   that asymmetry is your fail-safe story.
3. **The order of magnitude at each hop.** The bus frame is 270 µs; the controller period is 10 ms;
   the joint tick is 1 ms. Write them on the arrows and notice that the transport is not the bottleneck
   anywhere — which is worth knowing before you blame it.

> **CHECK YOURSELF** — From your own drawing: the controller manager runs at 100 Hz and the joint at
> 1 kHz. What is the joint doing for the nine ticks between commands? If your answer is "waiting", read
> the paragraph above again — the answer is the whole reason a soft-real-time machine is allowed to
> command a hard-real-time one.

> **WATCH OUT** — **`read()` and `write()` must not block.** They are called from the controller manager's
> real-time update loop. A blocking serial read here stalls every controller on the robot. Buffer in a
> separate thread and have `read()` copy the most recent value. This is the same discipline as
> Stage 1's "do not do heavy work in the timer ISR," one layer up — and it is the *third* time this
> project has made the same argument, which is a good sign you have found a real principle rather than
> a rule.
>
> Also note: the `ros2_control` migration script you may find online is only recommended for Foxy and
> Humble and is **not compatible with the API from Jazzy onwards.** Follow the current Jazzy docs.

### What will go wrong

- **The plugin does not load.** `pluginlib` errors are about the export XML, not your C++. Check the
  `<library path=...>` and that the class name in the XML exactly matches the URDF `<plugin>` string.
- **It loads, activates, and every state reads zero.** `read()` is being called and your parsing is
  failing silently. Print the raw bytes the gateway sent, once, before you touch anything else.
- **The arm moves the wrong way, or twice as far as commanded.** Units. The interface speaks
  **radians**; your firmware speaks **counts**. There is exactly one place that conversion should
  happen, and it should use the measured counts-per-revolution from S2.4's motor change — not the
  Stage 0 figure, which is now wrong.
- **Everything works and then stutters every few seconds.** Your transport is blocking, or the
  gateway's buffer is filling. Watch the controller manager's own update-period statistics rather
  than guessing.
- **The controller reports a goal failure with no obvious cause.** Trajectory tolerances. You left
  them as a TODO in S2.8; a real arm with real lag will violate default tolerances that mock hardware
  never did. Set them deliberately now.

**Capture the broken state.** The raw bytes the gateway actually sent, printed once, while every
state interface still reads zero. Screenshot the terminal. This is the session with the most moving
parts in the project and its characteristic failure is silent parsing — `read()` is being called, it
is failing, and nothing says so. The raw bytes are the one place the truth is, and printing them is
the first thing to do rather than the last.

### Prove it

The same trajectory, run three times: in mock, in Gazebo, and on hardware, from the same launch file
with only the argument changed. Plot all three on one set of axes. They will not be identical, and
the *differences* are the interesting part — that gap is everything your simulation does not know
about your machine.

### Artifacts

- **`docs/sessions/hardware-interface/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `mimic_hardware/` package, with the plugin XML export.
- The gateway firmware, in `firmware/stage2-gateway/`, with its serial framing documented alongside
  `docs/protocol.md`.
- The three-way overlay plot.
- The gateway-transport ADR in `docs/decisions/` — serial bridge vs micro-ROS, and why in that order.
- The gateway-hardware ADR in `docs/decisions/` — ESP32-S3 or second Nucleo, and what it costs you in
  spare boards.
- **Site:** the three-way overlay — mock, Gazebo, hardware, same launch file, same trajectory, one set
  of axes. The gap between the traces is everything your simulation does not know about your machine,
  and being able to point at it and name the causes is a much stronger claim than a video of the arm
  moving.
  **The shot:** one plot, three traces, one set of axes, with a legend naming mock, Gazebo and
  hardware. The gaps between them are the artifact, so do not smooth or rescale to make them
  agree.

---

## S2.12 · Homing and calibration

**Goal:** an arm that knows where it is at power-up.

**You will be able to:** explain why an incremental encoder needs homing and an absolute one does not, and derive a homing speed from switch bounce and loop rate rather than picking one that feels safe.

### Concept

Incremental encoders do not know where they are when powered on — they know how far they have moved
since. Every real robot resolves this on boot, and building it now is far easier than retrofitting it.

### The build

1. Drive slowly toward a limit switch (you bought ten roller-lever switches in the Stage 0 order).
2. On contact, stop and zero the count.
3. Back off to a known safe pose.
4. Set the `homed` flag. **Refuse all motion commands until homed** — the flag was already in your
   Stage 0 `JointState` for this reason.

**Homing speed matters.** Too fast and the switch bounces or the arm overshoots into the hard stop.
A rate limit of roughly 0.3 rad/s during homing, versus your normal 3 rad/s, is a reasonable start.

**Derive that number rather than accepting it.** A cheap roller-lever microswitch has a few
milliseconds of contact bounce, and your control loop samples it at 1 kHz. The distance the joint
travels between the switch actually closing and your firmware acting on a debounced reading is:

```
overshoot = homing speed × (debounce window + one control period)
          = 0.3 rad/s × (0.005 s + 0.001 s)
          = 0.0018 rad = 0.10°

at your normal 3 rad/s the same latency gives 0.018 rad = 1.03°
```

Put those against your encoder rather than against intuition. One count is 0.043° on the N20 and
0.030° on the JGB37-520, so **0.10° is two or three counts** — small enough to vanish into noise you
already tolerate. **1.03° is twenty-four counts on the N20 and thirty-four on the JGB37-520**, which is
a real and repeatable offset in your zero. That
factor of ten is the entire argument for a separate homing speed, and it is worth computing in counts
rather than degrees because counts are the units your repeatability is actually measured in. Repeat the homing sequence ten times and
record the spread of the zero position — **that spread is your homing repeatability, and it is a
number you should be able to quote.** Write all ten zeros into `docs/tuning/homing-repeatability.md`
as you take them, in counts as well as degrees, rather than only the spread you compute at the end.
The ten values show whether it is scatter or drift, and the spread alone cannot. Anything worse than a few tenths of a degree means the switch
mounting flexes, which is a mechanical fix and not a software one.

### Draw this

**The homing sequence as a state machine, and the switch geometry beside it.** States: unhomed,
seeking, backing off, homed. Arrows labelled with what causes each transition. Then mark the one that
is not obvious — what happens when the arm starts on the *far* side of the switch and seeking drives it
away from the switch and into the hard stop.

Beside it, draw the switch and the actuating feature to scale: where the lever contacts, how much
overtravel there is before the hard stop, and how far the joint moves in that overtravel at your homing
speed. If your overshoot arithmetic says 0.1° and the mechanical overtravel is less than that, the
switch is the hard stop and you will break it.

### What will go wrong

- **Homing works from one side and drives into the hard stop from the other.** You are homing in a
  fixed direction from an unknown position. Decide what happens when the arm starts on the far side of
  the switch, and test it deliberately.
- **The zero moves a degree or two between runs.** Switch mount flex, or you are zeroing on the raw
  contact rather than on a debounced edge. Both are visible in the ten-trial spread.
- **The AS5600 reads a plausible angle that is wrong.** Axial magnet instead of diametric. They look
  identical, and this failure is silent — the reading is smooth and stable and simply does not
  correspond to the shaft.
- **Two AS5600s and only one responds.** Both are hardwired to `0x36`. This is not a wiring fault; it
  is an address collision, and no amount of rewiring fixes it without the multiplexer.
- **The arm accepts a motion command before homing.** The `homed` flag is not being checked on the
  path the command actually took. Test it by commanding motion at power-up, every time.

**Capture the broken state.** The arm homing away from the switch and into its hard stop, because it
started on the far side. Film it — carefully, with a finger on the e-stop, and once. It is the
failure that turns homing from a four-step recipe into a design decision about what to do from an
unknown starting position, and it is much more persuasive seen than described.

### Prove it

> **CHECK YOURSELF** — Predict your homing repeatability in *counts* before you run the ten trials.
> You have a homing speed, a debounce window and a loop rate; the overshoot arithmetic above gives you
> a number. If the measured spread is much worse than your prediction, the extra is mechanical — switch
> mount flex — and no amount of software will remove it.

Ten homing cycles from ten different starting poses, including one from each side of the switch.
Record the resulting zero each time. Then power-cycle and confirm the arm refuses to move until homed.

### Artifacts

- **`docs/sessions/homing/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- `docs/tuning/homing-repeatability.md` — the ten trials and the spread.
- The homing ADR in `docs/decisions/` — switch vs AS5600 vs both, and the direction rule.
- **Site:** the repeatability number, stated plainly — "homes to within 0.2° over ten trials from ten
  starting poses." One number, and it is the kind of number a manufacturer quotes.
  **The shot:** the number, as text, in a sentence. If you want an image, the ten trials as a
  strip plot with the spread annotated — but the sentence is the artifact and it works without
  one.

### The AS5600 alternative, and its trap

You own two AS5600 boards, and an absolute encoder on the joint axis removes the homing sequence
entirely — it knows the angle at power-up. Two things to know:

- **Both AS5600s are hardwired to I²C address `0x36` and it cannot be changed.** Two of them on one
  bus requires a **TCA9548A I²C multiplexer** — Tier D2 of *What's Left to Buy*, qty 2, about C$2.50
  each, and there is a WATCH OUT on it in the Project Guide's Chapter 4. Order it with the rest of
  Tier D; without it, two-joint absolute encoding does not work at all.
- The magnet must be **diametric, not axial**. They look identical and an axial magnet silently gives
  you nonsense.

Best practice is both: AS5600 for absolute position, limit switches as end-of-travel safety. They fail
in different ways, which is the point.

**A homing ADR in `docs/decisions/` is where that lands**, and it has two halves rather than one:
switch, AS5600 or both — and, separately, **the direction rule**, which is what the joint does when
it powers up on the far side of the switch. The second half is the one people leave out, it is the
failure at the top of the list above, and it is a decision rather than an implementation detail.

---

## S2.13 · MoveIt 2 and Cartesian commands

**Goal:** command the gripper to a point in space and watch coordinated multi-joint motion happen.

**You will be able to:** command a pose rather than a set of angles, and check a planner's answer against kinematics you derived yourself — including knowing which of you to believe when they disagree.

This is the moment it stops being two motors and becomes a robot.

### Concept

Everything up to now has commanded *joints*. MoveIt commands *poses* — you say where the tip should
be and it produces a time-parameterised trajectory that gets there without hitting anything, which
your `joint_trajectory_controller` then executes. Two new ideas arrive at once: planning in a
configuration space with obstacles in it, and trajectories that respect velocity and acceleration
limits rather than being step commands.

For a two-link planar arm most of MoveIt's machinery is overkill, and that is fine — the reason to use
it is that it is the standard, it is what a job posting means by "MoveIt experience," and it gives you
a second, independent implementation of the IK you derived by hand.

**That paragraph is the substance of a planning ADR in `docs/decisions/` and you should write it
yourself rather than inherit it.** A sampling planner on a 2-DOF arm is a real over-engineering
choice with a real justification, and "I used the standard tool knowing a joint-interpolated plan
would have done, because the standard tool is the transferable skill" is a better answer than either
using it unthinkingly or rejecting it as overkill.

### Build

Configure MoveIt 2 with the Setup Assistant, define your planning group and its limits, and command a
pose. **Then check MoveIt's answer against your own IK from S2.3.** They should agree to within
numerical noise. Where they do not, work out which is wrong — MoveIt is more likely correct, and
finding out *why* your derivation disagrees is worth more than the derivation being right first time.

Add the bench and the plank as collision objects in the planning scene. An arm that plans a beautiful
path through your desk is a demonstration that the planner believed you when you told it the world was
empty.

> **LOOK THIS UP** — The official **MoveIt 2 tutorials** are the primary source, and **Antonio Brandi's**
> manipulator course covers the URDF → ros2_control → MoveIt path end to end on a small arm, which is
> exactly this project's shape. Work the Setup Assistant tutorial first; the concepts make far more
> sense once you have seen the generated config.

### Draw this

**The ten targets on your workspace annulus, before you command any of them.** Plot the annulus to
scale from S2.2, mark your ten Cartesian targets on it, and for each one sketch the arm pose your own
IK will produce. Mark which are near the outer boundary, which are near the elbow limit, and which are
comfortably in the middle.

That drawing is your prediction of where MoveIt and your solver will disagree, and it turns the
comparison table from a list of numbers into a test of a hypothesis. It also catches the target you
accidentally placed inside the 47 mm hole before the planner refuses it and you spend an hour on the
planner.

### What will go wrong

- **MoveIt plans, reports success, and the arm does not move.** The commonest failure in this session.
  MoveIt's controller configuration lists a controller name and an action type that must match what
  `ros2_control` actually exposes. Check `moveit_controllers.yaml` against
  `ros2 control list_controllers`, and check the action name with `ros2 action list`.
- **Planning fails immediately for reachable targets.** Your joint limits in the SRDF or URDF exclude
  the solution branch. Remember S2.8: you committed to positive θ₂, so an elbow-down pose is now
  genuinely unreachable and MoveIt is right to refuse it.
- **The planner takes seconds and returns wandering paths.** Normal for a sampling planner on an
  under-constrained problem. For a 2-DOF arm, a Cartesian-path or a simple joint-interpolated plan is
  often the better tool, and knowing when *not* to sample is a real answer.
- **It works in rviz2 and not on hardware.** The trajectory MoveIt produces respects the velocity and
  acceleration limits in your URDF. If those are placeholders, it will command motion your arm cannot
  physically follow, and the controller will fail on tolerance. Set them from S2.4's real motor speeds.

**Capture the broken state.** MoveIt reporting a successful plan while the arm sits completely
still. Screen-record rviz2 executing a trajectory next to hardware that has not moved. It is the
commonest failure in this session, it is a controller-name mismatch rather than anything to do with
planning, and the recording of a confident planner talking to nothing is the most recognisable thing
in Stage 2 for anyone who has run this stack.

### Prove it

> **CHECK YOURSELF** — Before you run the comparison: where do you expect the largest disagreement, and
> why? Near the workspace boundary, near the singularity, or evenly spread? Your answer is a prediction
> about *your own solver's* weak points, and checking it is worth more than the table agreeing.

A table of ten Cartesian targets with three columns: your S2.3 IK solution, MoveIt's solution, and the
difference. Then the same ten executed on hardware, with the measured tip position.

### Artifacts

- **`docs/sessions/moveit/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- The comparison table — this is exit criterion 5.
- The planning ADR in `docs/decisions/` — planner choice, and why for a 2-DOF arm.
- **Site:** the comparison table itself. Ten Cartesian targets, your hand-derived IK, MoveIt's answer,
  and the difference — with the largest disagreement explained. Agreeing with a standard solver you
  did not write is a much better claim than using one.
  **The shot:** the table itself, rendered as a table rather than photographed, with the largest
  disagreement highlighted and one line of prose explaining it.

---

## S2.14 · Record and replay

**Goal:** `ros2 bag` capturing every joint state, command, gripper state and diagnostic; replayed and plotted.

**You will be able to:** record and replay a running robot, and compute the same four step-response numbers from a bag that you computed from a CSV in Stage 0 — a claim about your instrumentation, not about your robot.

### Concept

A bag is the ROS 2 equivalent of the CSV pipeline you built in Stage 0 S7 — with the difference that
you do not have to write it, and it captures *everything* rather than the four fields you thought to
log. Every debugging session after this one starts with "record it, then look at it offline," which is
a far better position than reproducing an intermittent fault live.

It is also the exact substrate that imitation learning needs, which is why Appendix E lists
learning-from-demonstration as a natural extension: a bag of teleoperated pick-and-place runs *is* a
demonstration dataset.

### Build

1. Record everything relevant in one go, and name the topics explicitly rather than using `-a` — an
   all-topics recording includes camera frames in Stage 3 and becomes unmanageable.
2. Replay it and confirm rviz2 shows the arm moving. Note that replay publishes `/joint_states`, so
   nothing else should be publishing them at the same time.
3. Write one plotting script that takes a bag and produces the same step-response metrics your Stage 0
   `plot.py` produced. Same four numbers, one layer up.

### Draw this

**The topic graph you intend to record, before you record it.** Every topic, its rate, and its
approximate message size — then multiply through to bytes per second and total it. One page, and it
tells you the bag size before you make one rather than after.

Mark on it the topics you are recording because you need them and the ones you are recording because
they were there. In Stage 3 that distinction is the difference between a 300 kB bag and a 1.6 GB one,
and the discipline is easier to build now, on a graph small enough to draw.

### The math — what a bag costs you

Size the recording before you make a habit of it:

```
2 joints × (position + velocity + effort) at 100 Hz, plus commands and diagnostics
   ≈ 20 float64 values per tick, plus per-message header overhead
   ≈ a few hundred kB per minute of arm motion

Stage 3 adds a 640×480 colour camera at 30 fps, uncompressed:
   640 × 480 × 3 × 30  ≈  27 MB per second  ≈  1.6 GB per minute
```

That four-order-of-magnitude jump is the reason the LFS warning below exists, and the reason you
should record compressed image topics rather than raw ones from the day the camera arrives.

> **WATCH OUT** — Bag files bloat repositories fast. Your `.gitattributes` should already have Git LFS
> tracking `*.db3` and `*.mcap` from the day you scaffolded the repo. Confirm `git lfs install` has
> actually been run on this machine before the first bag lands — rewriting history to remove a 400 MB
> file is a bad evening.

### What will go wrong

- **The bag is enormous after thirty seconds.** You used `-a` and picked up camera topics, or you are
  recording raw images rather than compressed ones. Name your topics explicitly.
- **Replay looks right in rviz2 and the arm does not move.** Correct — replay publishes *recorded*
  joint states, it does not command anything. If the real arm *does* move during replay, something is
  subscribing that should not be, and that is worth finding.
- **Replay and a live publisher fight.** Both are publishing `/joint_states` and rviz2 shows the arm
  flickering between two poses. Stop the live source, or remap one of them.
- **Timestamps in the plot are wrong or bunched.** You are plotting the *received* time rather than the
  message header stamp. For a step response that difference is the whole measurement.
- **`git status` shows a 400 MB file.** LFS was never initialised on this machine. `.gitattributes`
  alone does nothing — `git lfs install` is a separate act, and rewriting history to undo this is a bad
  evening.

**Capture the broken state.** The `ls -lh` on a bag that is enormous after thirty seconds.
Screenshot it beside the arithmetic from the section above that predicted a few hundred kilobytes.
The gap between a computed estimate and a real number is the session, and once you have deleted the
bag the number is gone.

### Prove it

> **CHECK YOURSELF** — Before you compute them: your Stage 0 rig and this arm are different machines
> with different motors, gearing and inertia. Which of the four numbers do you expect to have changed
> the *most*, and in which direction? Commit to an answer — the point of computing the same four metrics
> three stages later is to be able to say what changed and why, not merely that you can still compute
> them.

Record a step response on hardware, replay it, and produce rise time, overshoot, settling time and
steady-state error from the bag — the same four numbers, computed by a different pipeline, on a
different machine, three stages later. If they match your Stage 0 methodology, your instrumentation
has survived the whole project intact, and that is worth a sentence on the site.

### Artifacts

- **`docs/sessions/record-and-replay/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- One recorded bag in LFS, and `tools/plot_bag.py`.
- The four step-response metrics, computed from the bag.
- **Site:** those four numbers beside the Stage 0 plot they were first computed from. Same metrics,
  different pipeline, different machine, three stages apart — a claim about your instrumentation
  surviving the whole project, and one very few portfolios can make.
  **The shot:** the four numbers as text beside the Stage 0 plot they were first computed from.
  Both sets of numbers must be readable in one view — that juxtaposition is the claim.

---

## The Stage 2 exit gate

| # | Criterion | Evidence |
|---|---|---|
| 1 | The arm moves in Gazebo and in reality from the same commands | Side-by-side video |
| 2 | A Cartesian target produces coordinated motion | Video |
| 3 | rviz2 shows the real arm's live state | Screen capture |
| 4 | You can derive FK **and** IK on paper without notes | Do it, filmed or photographed |
| 5 | Your IK agrees with MoveIt 2 | Comparison table |
| 6 | Homing works reliably from any starting pose | Ten trials logged |
| 7 | You computed the torque budget and chose actuation on evidence | `docs/decisions/` |
| 8 | You can explain your singularity limits and why they are where they are | `docs/derivations/` |
| 9 | The gripper picks up and holds a 100 g object, ten times out of ten | Video |
| 10 | Your torque budget uses **measured** masses, not assumed ones | Updated `docs/derivations/` |
| 11 | A recorded bag replays and plots | The bag, in LFS |
| 12 | The gateway runs firmware you wrote, and you can drive the arm from `screen` with no ROS 2 running at all | Terminal transcript |
| 13 | Tag `v0.2-stage2-exit` pushed | GitHub |

---

## What goes on the site, in order

Same principle as Stage 0 and Stage 1: chronological rather than curated, each item dated, each one a
step forward. Stage 2 is the longest stage and produces the most showable material, so the risk here
is not having too little — it is finishing the arm and never having captured the parts that made it.

| Session | The artifact | Why it reads well |
|---|---|---|
| S2.2 | Workspace annulus, to scale, with your bench on it | Shows you thought about where it *cannot* reach |
| S2.3 | The handwritten IK derivation | Handwritten algebra for a machine you then built is the single most differentiating thing in the project |
| S2.4 | The free-body sketch and the ADR | An engineering decision with its arithmetic attached |
| S2.5 | CAD render beside the S2.4 free-body sketch | The same arm drawn twice, once by hand with the maths on it |
| S2.6 | Slider capture beside your hand-drawn frame tree | Anyone can show a model moving; almost nobody shows the drawing it came from |
| S2.7 | Falling under gravity, then holding | Ten seconds that prove the simulation has physics rather than geometry |
| S2.8 | One paragraph on the seam | "Three hardware backends, one line" — most people who list `ros2_control` cannot say it |
| S2.9 | Real arm beside the Gazebo render, same pose | Needs no caption |
| S2.10 | Video of it picking something up | The first moment the arm looks like it has a purpose |
| S2.11 | The three-way overlay: mock, sim, hardware | The gap between the traces is what your simulation does not know |
| S2.12 | The homing repeatability number | One number, of the kind a manufacturer quotes |
| S2.13 | Your IK against MoveIt's, ten targets | Agreeing with a solver you did not write beats using one |
| S2.14 | The same four metrics, from a bag, three stages later | A claim about instrumentation surviving the project |

---

## The milestone map

The Project Guide numbers Stage 2 as milestones **M2.1–M2.10**; this workbook numbers it
**S2.0–S2.14**. Same work, two levels of detail. Every milestone in the set carries its stage as a
prefix, so `M2.6` is unambiguously Stage 2's sixth and not Stage 0's or Stage 1's.

| Guide milestone | Workbook session | Note |
|---|---|---|
| **M2.1** · Derive the kinematics on paper | **S2.2** + **S2.3** | FK, then IK and the Jacobian |
| **M2.2** · Compute the torque budget | **S2.4** | The one that changes your parts list |
| **M2.3** · Design the arm in CAD | **S2.5** | |
| **M2.4** · Write the URDF and see it in rviz2 | **S2.6** | |
| **M2.5** · Simulate in Gazebo Harmonic | **S2.7** + **S2.8** | Gazebo, then `ros2_control` against mock hardware |
| **M2.6** · Print and assemble, and build the gripper | **S2.9** + **S2.10** | |
| **M2.7** · Write the `ros2_control` hardware interface | **S2.11** | Also where the gateway node is built |
| **M2.8** · Homing and calibration | **S2.12** | |
| **M2.9** · MoveIt 2 and Cartesian commands | **S2.13** | |
| **M2.10** · Record and replay | **S2.14** | |
| *(no Guide milestone)* | **S2.0** · Host, proven | Infrastructure, deliberately not a milestone |
| *(no Guide milestone)* | **S2.1** · ROS 2 fundamentals | Learning someone else's conventions is not an achievement |

---

## Session index

| # | Session | Hours | Blocking on |
|---|---|---|---|
| S2.0 | Host, proven | 4 | Ubuntu install |
| S2.1 | ROS 2 fundamentals | 15 | — |
| S2.2 | Forward kinematics | 3 | — |
| S2.3 | Inverse kinematics, singularities | 5 | — |
| S2.4 | **Torque budget** | 3 | — |
| S2.5 | CAD | 15 | Printer decision |
| S2.6 | URDF and rviz2 | 6 | — |
| S2.7 | Gazebo Harmonic | 8 | — |
| S2.8 | ros2_control, mock hardware | 8 | — |
| S2.9 | Print and assemble | 20 | **Print time** |
| S2.10 | **The gripper** | 6 | Printer |
| S2.11 | Hardware interface | 12 | Stage 1 firmware |
| S2.12 | Homing and calibration | 5 | — |
| S2.13 | MoveIt 2 | 10 | — |
| S2.14 | Bag and replay | 3 | — |
| | **Total** | **~123 h** | |

Eight weeks at your pace. The number that does not compress is S2.9: an arm link is a six to
twelve hour print, and the loop is design, print, discover a tolerance is wrong, redesign, reprint —
two or three times per part. Run firmware work while the printer runs.

---

## Figure index

Every figure in this document is plain ASCII/box-drawing art inside a fenced code
block, tagged `FIGURE <id> — <title>` on its first line. That is deliberate: it
renders correctly in GitHub and in any Markdown viewer, and it stays diffable in
Git. For a PDF export, set the monospace font to one with full box-drawing and
half-block coverage — **DejaVu Sans Mono** is the usual answer; the core PDF
monospace fonts do not carry the geometric and box-drawing characters these figures use — in this
volume: `╭ ╮ ╰ ╯ ═ ╪ ╱ ╲ ▓ ◄ ► ▼ ← → ↻ ✗ ≈ ≤ · ●` — and will drop or substitute them.

| Figure | Title | Where |
|---|---|---|
| **S2.2.1** | The geometry everything in Stage 2 refers back to | S2.2 |
| **S2.4.1** | Free body, arm fully extended horizontally (the worst case) | S2.4 |
| **S2.8.1** | The seam, and the one line that moves it | S2.8 |
| **S2.10.1** | Where grip force comes from | S2.10 |
