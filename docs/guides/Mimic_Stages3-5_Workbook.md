# Mimic — Stages 3, 4 and 5 Workbook

**Volume VI · Eyes, Voice, Muscle, and Compliance**

The last three stages, at milestone depth rather than session depth — and a note on why.

---

## Why this one is less granular, on purpose

Stages 0 through 2 got session-by-session treatment because they are built on hardware you own or can
specify now, and because their failure modes are physical and predictable.

Stages 3 to 5 are months out — Stage 3 starts around month five of a seven-month calendar (Project
Guide Appendix G), and Stage 5 is open-ended after it. Their content is almost entirely software, and
the software moves: the speech and language model landscape in particular will not look the same when you
arrive. Writing "install package X version Y" today would produce instructions that are wrong by the
time you read them, with the specific danger that wrong instructions are worse than none — you would
spend a day fighting a stale tutorial instead of ten minutes reading a current one.

So this volume gives you the **structure, the mathematics, the decisions, and the traps** — the parts
that do not go stale — and points at the current documentation for the parts that do.

**Write the Stage 3 sessions when you reach the Stage 2 exit gate.** By then you will know what your
arm actually is, and the sessions can be specific.

---

## The standing rule, and why these stages are the ones it was written for

**Capture the broken state before you fix it.** Each milestone's *What will go wrong* ends by naming
the one worth catching.

Everywhere earlier in this project, the broken state was evidence of your working. Here it is
frequently **the result itself**, and that is the difference worth understanding before you start
deleting things.

Three of these milestones produce their most valuable artifact in the "before" condition:

- **M3.3's hand-eye residual.** The scatter of misses *before* you solve `AX = XB` — tight, and
  offset in one direction — is the thing that makes the after-scatter mean anything. Solve the
  transform without recording it first and the result is a number with nothing to compare against.
  **It is unrecoverable the instant the transform is solved**, and that milestone says so twice.
- **M4.3's fatigue plot.** A threshold that works rested and fails after two minutes of effort *is*
  the argument for M4.4. The failure is the finding.
- **M4.4's cross-session gap.** 98 % within a session against 60 % across days is the central
  unsolved problem of myoelectric control, honestly measured. Reporting only the first number is
  the thing that milestone exists to stop you doing.

So the framing shifts. Earlier stages: capture the failure so the write-up is credible. **Here:
capture the failure because it is the measurement**, and a stage that reports only its successes has
not reported its work.

One practical note, since Stage 4 involves your own body. The safety artifact in M4.2 — your
hand-drawn isolation topology — is the opposite case and worth naming as such: **it is dated evidence
that you reasoned before you connected**, so it is captured *before* anything happens rather than
when something goes wrong.

---

# STAGE 3 — EYES AND VOICE

**About eight weeks at hobby pace, three to four at yours. Cost: C$0–70 — see Tier E of *What's Left to Buy*; nothing at all if you already own a webcam and a microphone.**

**You will own:** an arm that finds an object with a camera and picks it up when you ask it to, out
loud, with no cloud service involved.

---

## Why this stage exists

Everything so far made the arm capable. This makes it commandable by a human who is not a
programmer — which, for assistive technology, is the entire point. A device that requires you to type
joint angles is not assistive.

It is also the stage that makes the project legible to other people. "I built a robot arm" produces
polite interest. "I built a robot arm that I talk to" produces a conversation.

**FIGURE VI.1** is the whole stage on one page. Two independent input chains — one visual, one
spoken — converge on a single planner, and everything downstream of that convergence is Stage 2 code
you have already written. Read it before the milestones; each one below is a labelled box on it.

```
FIGURE VI.1 — The Stage 3 pipeline, and where each milestone sits

  ┌──────────┐  M3.1  ┌────────────┐  M3.2  ┌──────────────┐
  │ USB      │───────►│ intrinsics │───────►│ ArUco detect │
  │ webcam   │        │ + distort. │        │ → pose, in   │
  └──────────┘        │ (one-time) │        │  CAMERA frame│
                      └────────────┘        └───────┬──────┘
                                                    │  M3.3
                                            ┌───────▼──────┐
                                            │ hand–eye     │  AX = XB
                                            │ camera_link  │  solved once
                                            │ → base_link  │
                                            └───────┬──────┘
                                                    │ pose in BASE frame
   ┌──────────┐ M3.5 ┌──────────┐ M3.6 ┌────────┐   │
   │ mic      │─────►│ whisper  │─────►│ intent │   │
   └──────────┘      │ (local)  │      │ + slots│   │
                     └──────────┘      └────┬───┘   │
                                            │       │
                                       ┌────▼───────▼────┐  M3.4
                                       │ plan → approach │
                                       │ → grasp → lift  │
                                       │ → place         │
                                       └────┬────────────┘
                                            │  open(f) / isHolding()
                                       ┌────▼────────────┐
                                       │ MoveIt 2 + arm  │  (Stage 2)
                                       └─────────────────┘
                            M3.7 speak back ◄── every failure path

  If the camera moves relative to base_link, M3.3 is void and every grasp
  is confidently wrong. Mount it rigidly and never adjust it casually.
```

---

## M3.1 · Camera, calibrated

**Goal:** an intrinsic matrix and distortion coefficients for your camera, with a reprojection error
you can quote — and no reason to touch the calibration again unless the optics change.

**You will be able to:** explain what an intrinsic matrix and a distortion model each describe, say why they are properties of the camera rather than of the scene, and quote a reprojection error and say what it means.

A USB webcam is fine. Run OpenCV's camera calibration with a printed checkerboard to recover the
**intrinsic matrix** and **distortion coefficients**.

**Write the reprojection error down the moment the script prints it**, into `docs/calibration/` with
the date, the camera's model number, the capture resolution and the number of images beside it. Every
one of those changes the number, and an error figure with none of them attached is not quotable —
you will not remember three months from now whether 0.4 px came from twenty images or from six.

### The math you should understand before running the script

The pinhole model maps a 3D point to a pixel:

```
    ⎡u⎤       ⎡fx  0  cx⎤ ⎡X/Z⎤
    ⎢v⎥  =    ⎢ 0 fy  cy⎥ ⎢Y/Z⎥
    ⎣1⎦       ⎣ 0  0   1⎦ ⎣ 1 ⎦
```

Note there is no scale factor `s` on the left. The right-hand vector is already divided by `Z`, so
the third row forces `s = 1` and writing it would be vacuous. The two correct forms are
`s·[u,v,1]ᵀ = K·[X,Y,Z]ᵀ` **or** the normalised one above — never both at once. The normalised form is
the clearer one to hold in your head, because it says plainly what a pinhole camera does: divide by
depth, then scale into pixels.

`fx, fy` are focal lengths in pixels; `cx, cy` the optical centre. Lens distortion is then corrected
by a radial polynomial in `k1, k2, k3` plus tangential terms `p1, p2`.

> **DEFINITION** — **Intrinsics, distortion coefficients, and extrinsics.** The **intrinsic matrix** is
> the 3×3 above: it describes the camera *itself* — focal length and optical centre in pixels — and it
> does not change when the camera moves. The **distortion coefficients** are the five (or more)
> numbers that describe how the lens bends straight lines, and they are also a property of the camera
> alone. Together those are what M3.1 recovers, once, and they are why the calibration is a one-time
> job. **Extrinsics** are the other half: the rotation and translation describing where the camera
> *is* relative to some other frame. They change the moment anything moves, and the fixed extrinsic
> between `camera_link` and `base_link` is precisely the unknown `X` that M3.3 solves for. Keeping the
> two words apart is worth the effort: an intrinsics problem is a lens problem and shows up as
> curvature, while an extrinsics problem is a geometry problem and shows up as a consistent offset.

> **WATCH OUT** — Calibration is unglamorous and everything downstream depends on it. An uncalibrated
> camera produces grasp positions that are confidently wrong — not noisy, *biased*, in the same
> direction every time, which is much harder to notice. Take 20+ checkerboard images at varied angles
> and distances, not 5 flat-on.

### Draw this

**The pinhole model, once, as geometry rather than as a matrix.** A pinhole on the left, an image
plane behind it, and one 3D point projecting through to a pixel. Mark the focal length as the
distance from pinhole to plane, mark the optical centre on the plane, and mark the similar triangles
that give you `u = fx·X/Z + cx` — because that division by `Z` is the whole of what a camera does and
the matrix is only bookkeeping on top of it.

Then, underneath, draw a straight line and the same line as a barrel distortion would bend it, and
label which coefficient does that. Two sketches, ten minutes, and the difference between
*intrinsics* and *distortion* stops being two words in the same sentence.

> **CHECK YOURSELF** — From your drawing: if you moved the camera twice as far from the scene, which
> of `fx`, `cx` and `k1` would change? If your answer is "none of them", say why in terms of the
> drawing rather than the definition — that is the difference between having read that intrinsics
> are a property of the camera and having understood it.

### What will go wrong

- **Reprojection error is 3 px and you cannot see why.** Not enough variety. Twenty images all taken
  flat-on from the same distance constrain the focal length and nothing else. Tilt the board, fill
  different parts of the frame, get close and far.
- **The board is not flat.** Paper glued to card curls. Every image is then subtly wrong in a way that
  averages into your intrinsics, and nothing in the output tells you.
- **Error is beautiful and grasps are still biased.** The webcam autofocused between calibration and
  use. Fixed focus is *better* here, and if yours cannot be locked, expect a bug that comes and goes.
- **You calibrate, then change the capture resolution.** Intrinsics are in pixels; change the
  resolution and every number is wrong by that scale factor.

> **CHECK YOURSELF** — Your `fx` will come out somewhere in the hundreds or low thousands. Before you
> run the calibration, work out roughly what to expect from your camera's field of view and its pixel
> width, and check the result lands near it. A calibration that converges to a confidently absurd
> focal length is what this check catches, and nothing else will.

**Capture the broken state.** The calibration reporting a 3 px reprojection error, screenshotted
next to the board images that produced it — twenty of them, all flat-on, all at the same distance.
It is a failure whose cause is visible in its own input data, which is unusual and worth showing.

### Artifacts

- **`docs/sessions/camera-calibration/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- **The reprojection error figure** — under ~0.5 px is good. This is the acceptance criterion for the
  milestone, so put the number itself in `docs/`, not just the plot.
- `docs/calibration/intrinsics.yaml` — the matrix and distortion coefficients, committed, with the
  date and the camera's model number beside them. They are only valid for that camera at that focus
  setting.
- The set of checkerboard images you calibrated from, so the result is reproducible.
- **Site:** the reprojection scatter, with the error quoted. It is a small plot that says you know
  what "calibrated" means.
  **The shot:** the reprojection scatter as a saved figure, with the mean error printed on the
  plot rather than in the caption, and the number of images it was fitted from beside it.

---

## M3.2 · ArUco markers before neural networks

**Goal:** a printed marker's full six-DOF pose, recovered from one image and published as a tf2
frame, so the arm can be told where something is in coordinates it already understands.

**You will be able to:** explain what PnP solves and why four known corners in one calibrated image are enough to recover a full six-DOF pose — and why starting with a neural network would have skipped the hard part.

Stick a printed fiducial on a block. Detect it, recover its full six-DOF pose from a single calibrated
image, publish it as a tf2 frame.

**Resist starting with an object detector.** This milestone teaches you the geometry, which is the
hard part. A neural network would hand you a bounding box and leave the actual problem — where is
that thing in the arm's coordinate system — completely untouched.

The pose recovery is solving **PnP** (perspective-n-point): given four known marker corners in 3D and
their pixel positions, find the rotation and translation. OpenCV does it; understand what it is doing.

### Draw this

**Four corners and one pose.** Draw the marker as a square in 3D with its four corner points
labelled, draw the camera, and draw the four rays from the camera through the four detected pixels
to those corners. Then write beside it what is known and what is not: the corners' positions *in the
marker's own frame* are known, because you printed it at a known size; the pixels are known, because
you detected them; the intrinsics are known, from M3.1. The unknown is the rotation and translation
between the two frames, and it has six numbers in it.

That is the entire statement of PnP, and drawing it is what stops the solver being a function you
call. Six unknowns, four points giving you eight equations — mark that on the page too, and notice
that it is over-determined, which is why the solver minimises an error rather than solving exactly.

Then draw the ambiguity: the same four pixels, and a *second* marker pose that would produce very
nearly the same ones when the marker is close to face-on. That second sketch is the failure in the
list below, and having drawn it you will recognise the flip on sight.

### What will go wrong

- **The marker is detected and the pose flips.** Ambiguous pose — a nearly face-on square has two
  solutions that project almost identically, and the solver alternates. Larger markers, more tilt, or a
  marker board rather than a single tag.
- **The pose is stable and the distance is wrong by a constant factor.** You told the detector the
  wrong marker size. It is a single number in metres and it scales everything.
- **Detection fails under your desk lamp.** Motion blur or glare. Fiducials want even lighting and a
  matte surface; a glossy print is much worse than a matte one.
- **The frame appears in rviz2 at the origin.** Published with no parent frame, or a zero timestamp, so
  tf2 cannot place it.

> **CHECK YOURSELF** — Hold the marker at a distance you can measure with a ruler and compare it against
> the pose the solver reports. Disagreeing by a constant ratio means the marker size is wrong;
> disagreeing more the further away it gets means your intrinsics are. **The shape of the error names
> the cause** — the same reasoning M3.3 uses for hand-eye, one step earlier.

**Capture the broken state.** The marker's axes flipping between two solutions while the block sits
still. Screen-record five seconds of it. Pose ambiguity on a near-face-on square is a real and
well-known problem, it looks like a bug in your code and is not, and a clip of axes snapping back
and forth is instantly legible where a paragraph about it is not.

### Artifacts

- **`docs/sessions/aruco-pose/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- A short video of the marker frame drawn on the live camera image, moving as you move the block.
- The tf2 tree, captured with `ros2 run tf2_tools view_frames`, showing `camera_link → marker`.
- `docs/decisions/` — the marker family and size you chose, and why. Marker size sets detection range
  and pose accuracy, and it is a decision people make by accident.
- **Site:** the overlay video. It is the first moment the project visibly *sees* something.
  **The shot:** one screen capture, 10 to 20 seconds, of the live camera image with the marker
  axes drawn on it while you move the block by hand. **Your hand in frame is worth having** — it
  is what makes it visibly live rather than a rendered animation.

---

## M3.3 · Hand-eye calibration

**Goal:** the fixed transform from `camera_link` to `base_link`, solved rather than measured with a
ruler — and a before/after number showing what solving it bought you.

**You will be able to:** explain what `AX = XB` is asking, say which arrows in the frame ring are known and which are not, and tell a calibration error from a noise problem by the *shape* of the error rather than its size.

The camera sees things in camera coordinates. The arm moves in base coordinates. Finding the fixed
transform between them is hand–eye calibration.

### The math

For a fixed camera watching the arm, you are solving the classic `AX = XB` problem: move the arm to
several poses with a marker on the gripper, and solve for the unknown transform `X` that makes the
camera's observations consistent with the robot's forward kinematics.

> **WATCH OUT** — This is the step people skip, and then wonder why the gripper always misses by two
> centimetres **in the same direction**. A consistent offset is the signature of a missing or wrong
> hand-eye transform. Random error is noise; consistent error is geometry.

### Draw this

**The transform chain, as a ring of frames**, because that ring is what `AX = XB` actually says and
the algebra is opaque until you have seen it.

Draw four frames as labelled circles: `base_link`, `gripper_tip`, `marker`, `camera_link`. Then draw
the arrows between them and mark each one as **known** or **unknown**:

- `base_link → gripper_tip` — known, it is your forward kinematics from S2.2
- `gripper_tip → marker` — fixed and unknown, but constant because the marker is glued to the gripper
- `camera_link → marker` — known per observation, from M3.2's PnP solve
- `camera_link → base_link` — **the unknown `X` you are solving for**

Now trace the ring in both directions and notice that it closes: going one way around must equal
going the other way, for *every* pose you record. That constraint, written for several poses at once,
is the whole method. Move the arm, and the two known arrows change while the two unknown ones do not
— which is why several poses pin down a transform that one pose cannot.

> **CHECK YOURSELF** — Point at the arrow that becomes invalid if you nudge the camera mount. If you
> pointed at `camera_link → base_link`, you have understood why FIGURE VI.1 ends with the warning it
> does. Every grasp after that nudge is confidently wrong, and nothing in the pipeline will tell you.

### Prove it

Record the gripper's miss distance over ten grasps **before** solving `AX = XB` and ten **after**,
and plot both as scatter. Before should be a tight cluster offset from the target; after should be a
looser cluster centred on it. That change in shape — from biased to unbiased — is the result, and it
is more convincing than either number alone.

**Capture the broken state.** The "before" scatter **is** the capture, and this milestone is the one
place in the project where forgetting it destroys the result rather than weakening it. Once the
transform is solved the biased state does not exist and cannot be reproduced — you would have to
deliberately un-solve a calibration you no longer have. Record the ten misses first. Everything else
in this milestone depends on there being something to compare against.

### Artifacts

- **`docs/sessions/hand-eye-calibration/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- **`docs/derivations/hand-eye.md`** — the before/after scatter plot and the two residual numbers.
  This is the highest-value artifact in Stage 3 and it cannot be reconstructed later, because once the
  transform is solved the "before" state is gone.
- The solved transform itself, committed, with the date and the number of poses it was fitted from.
- One line in the README: "missed by 23 mm in a consistent direction; after solving `AX = XB`, 2 mm in
  no particular direction" — with your numbers.
- **Site:** the two scatters side by side. Biased versus unbiased is legible to anyone in four
  seconds.
  **The shot:** two scatter plots at **identical axis limits**, before and after, side by side.
  The identical limits are the entire specification: rescale either one and the change from biased
  to unbiased disappears. Mark the target at the origin on both.

---

## M3.4 · Pick and place, closed loop

**Goal:** detect, plan, approach, grasp, lift, place — and a named, tested behaviour for each of the
three ways it can fail.

**You will be able to:** enumerate a pipeline's failure modes before writing its happy path, and say what each one should do — which is the difference between a demo and a system.

Detect, plan, approach, grasp, lift, place.

**Getting the failure paths right is most of the work.** What happens when the object is out of
reach? When the marker is occluded mid-motion? When the gripper closes and feels nothing? Enumerate
these before you write the happy path, because retrofitting failure handling into a working pipeline
is much harder than building it in.

The third of those is answerable because you built it: **`isHolding()` from S2.10** is what turns
"the gripper closed" into "the gripper closed *on something*", and it is the difference between a
pick-and-place that reports failure and one that confidently places nothing.

### Draw this

**The pick sequence as a state machine, with a failure arrow off every state.** Detect, plan,
approach, descend, grasp, lift, transit, place, retreat — one box each — and then the part that
matters: from every box, one arrow leaving downward for the way that step can fail, labelled with
how you *detect* it and where it goes.

Draw the failure arrows first if you can bear to. The workbook says to write the failure-mode table
before the happy path and this is the same instruction in a form you cannot fudge — a box with no
failure arrow is a step you have not thought about, and on a drawing that is visible at a glance
where in a list it is not.

Three arrows will be harder than the rest and they are the three the milestone is built around:
the target is unreachable, the marker is occluded once the arm is close, and the gripper closed on
nothing. The third is answerable only because S2.10 built `isHolding()`; mark on the drawing which
sensor answers each question, and if any arrow has no sensor beside it, you have found the thing to
build before the happy path.

### What will go wrong

- **The gripper arrives 2 cm short, every time, in the same direction.** Hand-eye, and M3.3 says so.
  Consistent means geometry; random means noise.
- **The approach is fine and the grasp knocks the object over.** You planned straight to the grasp pose
  instead of to a standoff above it and then down. Approach vectors are a design decision, not a
  planner setting.
- **The marker is occluded by the gripper at exactly the moment you need it.** Expected — the arm is
  between the camera and the object by the time it is close. Capture the pose *before* approaching and
  move open-loop from there, or mount the camera where the arm does not block it.
- **It reports success having grasped nothing.** `isHolding()` from S2.10 is not wired in, and that is
  the failure this whole milestone is built around.

> **CHECK YOURSELF** — Write the failure-mode table *before* the happy path, then predict which of the
> three failures you will hit first on real hardware. The answer is almost never the one people expect,
> and having guessed is what makes the bag recording worth keeping.

**Capture the broken state.** The arm completing a confident, textbook pick-and-place having grasped
nothing at all, and placing air. Film it. It is the failure this entire milestone is built around,
it is the reason `isHolding()` exists, and a pipeline that reports success while visibly holding
nothing makes the argument for failure handling better than any table of failure modes can.

### Artifacts

- **`docs/sessions/pick-and-place/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- **A failure-mode table**: each way the pipeline can fail — unreachable, marker occluded mid-motion,
  gripper closed on nothing — with the detection and the response for each. Written *before* the happy
  path.
- A recorded `ros2 bag` of one complete successful cycle, and one of each failure being handled.
- **Site:** the successful pick-and-place video, and — more usefully — one of the failures. A pipeline
  that notices it grasped nothing is worth more than one that never misses on camera.
  **The shot:** two clips. The successful cycle, 20 to 30 seconds, one take. And the more useful
  one: a failure being *noticed* — the gripper closing on nothing and the system saying so. For
  that second one the terminal or the spoken output must be captured too, because the point is the
  detection rather than the miss.

---

## M3.5 · Local speech to text

**Goal:** reliable text out of a microphone, on your own machine, with the network cable unplugged
and nothing interpreting it yet.

**You will be able to:** measure a speech pipeline rather than demonstrating it, and quote a word error rate taken in the room you actually use.

A Whisper-based ROS 2 node with **voice activity detection**, so it only transcribes when you are
actually speaking. Run it locally.

Confirm you get reliable text out **before** adding any interpretation layer. Debugging a language
model's behaviour while the transcription underneath it is also unreliable is the two-fronts problem
again.

`whisper_ros` and its companions by mgonzs13 are the established ROS 2 packages here — check what is
current when you arrive.

### Draw this

**Nothing.** A speech pipeline is a chain of black boxes with an accuracy figure at the end, and a
box diagram of microphone → VAD → model → text would be a drawing of the sentence you have just
read. The artifact here is the measured error rate and the conditions it was taken under, and those
are text.

### What will go wrong

- **Accuracy is excellent in testing and poor in use.** You tested in silence, close to the mic. Measure
  in the room, at the distance, with the arm running — a stepper and a fan sit in exactly the band
  speech does.
- **It transcribes the room continuously.** Voice activity detection is off or its threshold is wrong.
  Without it you are feeding silence to a model and getting invented text.
- **Latency makes it unusable.** Model size. This is the first place Stage 3 gets slow and it is a real
  trade-off — record what you chose and what it cost.
- **The first word is always missing.** VAD triggers on the sound and starts capturing after it. A small
  pre-roll buffer fixes it.

> **CHECK YOURSELF** — Before you measure it: what word error rate would make this usable? One in
> twenty commands misheard, one in a hundred? Commit to a number, then measure. A pipeline you can say
> "94 % on thirty commands, in the room, with the arm running" about is worth far more than one you can
> only demonstrate.

**Capture the broken state.** The transcript log itself, with the errors left in — taken in the room
you actually use, at the distance you actually stand, with the arm running. Do not re-record it
quietly and quote that number instead. A word error rate measured under realistic conditions is a
claim; one measured in silence six inches from the microphone is a different and much weaker claim
wearing the same units.

### Artifacts

- **`docs/sessions/speech-to-text/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- A transcript log of thirty spoken commands with the word error count, taken in the room you will
  actually use. Quiet-room accuracy is not the number that matters.
- `docs/decisions/` — model size chosen, and the latency it costs. This is a real trade-off and it is
  the first place Stage 3 gets slow.
- **Site:** one line of measured transcription accuracy. Everyone demos speech; almost nobody quotes
  an error rate.
  **The shot:** one line of text with the measured rate, plus the transcript log as a readable
  block — the errors left in, and one line stating the conditions: the room, the distance, and
  whether the arm was running.

---

## M3.6 · Language to intent

**Goal:** a structured, validated command — action name plus bounded parameters — produced from that
transcript, with malformed output rejected rather than repaired.

**You will be able to:** state why a model's output must be validated before it reaches anything that moves, and express that as a schema with bounds rather than as an intention.

A local language model takes the transcript and emits a **structured command** — an action name and
parameters — rather than prose.

> **WATCH OUT** — **Never let a model's output reach the motion layer unvalidated.** It should select from
> a fixed set of actions with bounded parameters, and your code should check reachability and joint
> limits before anything moves. This is not paranoia about models — it is the same discipline you
> would apply to any untrusted input, and it is exactly the habit safety-critical work demands. Design
> it as: **the model proposes, your code decides.**

Constrain the output format hard. Validate it. Reject anything malformed rather than trying to repair
it — a repaired malformed command is a command nobody specified.

### Draw this

**The validation boundary, as a line across the page with the model above it and the arm below.**
On the line, draw the only thing that crosses: one structured command, an action name and its
parameters. Then write on the model's side everything it is allowed to do — propose — and on your
side everything you do: check the action is in the fixed set, bounds-check every parameter, run
reachability through S2.3's IK, and reject.

Mark the arrow that does **not** exist: there is no path from the model to the motion layer that
does not pass through your validator. If your drawing has one, that is a design you should change on
paper tonight rather than in code later.

Then write three malformed commands under the line and trace each one to where it dies. A valid
action with an out-of-range parameter, a syntactically perfect command for an action you never
defined, and a reachable target whose *approach* is not reachable. Those three become your test file,
and the drawing is what makes them obvious.

### What will go wrong

- **The model returns prose with the JSON embedded in it.** Constrain the output format hard, and parse
  defensively rather than trusting the shape. Never `eval` it.
- **It returns valid JSON with an action you never defined.** This is the case the validator exists for.
  Reject; do not map it to the nearest known action, because "nearest" is a guess about intent and this
  is the layer where guessing stops.
- **It returns a valid action with a plausible, unreachable pose.** Bounds-check every parameter
  *and* run reachability — S2.3's IK already returns failure for unreachable targets, so use it.
- **It repairs a malformed command and you let it.** A repaired command is a command nobody specified.
  This is the one to be strict about, and it is the habit the whole milestone is teaching.
- **Latency doubles because the model is re-loaded per request.** Keep it resident.

> **CHECK YOURSELF** — Write down three commands a *malicious* or careless speaker could produce that
> pass a naive validator: a valid action with an out-of-range parameter, a reachable target with an
> unreachable approach, and a syntactically perfect command for an action that does not exist. Those
> three go in your test file before the happy path does.

**Capture the broken state.** The model's raw output the first time it returns prose with the JSON
buried in it, or a syntactically perfect command for an action you never defined. Screenshot it
verbatim. **That output is the justification for the entire validation layer**, and it is far more
convincing than the argument for one — an interviewer reading a real malformed command next to the
validator that rejected it does not need the argument.

### Artifacts

- **`docs/sessions/language-to-intent/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- **The command schema** — the fixed action set and the bounds on every parameter — committed as a
  file, because it is the contract the validator enforces.
- The validator, and a test file of malformed and out-of-bounds commands that it rejects. Include the
  adversarial ones: a reachable pose with an unreachable approach, a valid action with a nonsense
  parameter.
- `docs/decisions/` — "the model proposes, my code decides", stated as a design rule with the
  reasoning.
- **Site:** the schema and the rejection tests. This is the artifact that reads as safety-critical
  habit rather than a demo.
  **The shot:** two blocks of readable text side by side: the schema, and the rejection test
  output showing malformed commands being refused. Include at least one adversarial case. This is
  an artifact made entirely of text and it is stronger for it.

---

## M3.7 · Speak back

**Goal:** the arm confirms what it is doing and says why when it refuses, out loud.

**You will be able to:** explain why a refusal is worth more than a confirmation in assistive technology, and keep the phrases the system can say as data rather than scattered through code.

Text to speech for confirmations and refusals. *"Moving to the blue block." "I can't reach that."*

Closing the loop conversationally matters more for perceived quality than any other single thing in
this stage, and refusals matter more than confirmations — a device that fails silently feels broken,
while one that says why feels considered.

### Draw this

**Nothing to sketch, but one table to write** — and it is a table rather than a diagram on purpose.
Every condition under which the arm refuses to move, in one column, and the distinct sentence it
says for each in the other: out of reach, not homed, gripper already full, IK failed, e-stop
latched. Keyed by condition rather than kept as a list of strings.

If two rows share a sentence, the person listening cannot tell those two states apart — and neither
can you, at the bench, three weeks later. That is the whole content of this milestone and a diagram
would not carry it.

### What will go wrong

- **Speech synthesis blocks the motion loop.** Generating audio is slow. Speak from a separate node or
  thread, and never from anywhere on the path that moves the arm — the same discipline as S1.4's ISR
  and S2.11's `read()`, for the third time.
- **It talks over itself.** Two refusals in quick succession queue or overlap. Decide which, and make
  it a queue with a maximum length rather than a race.
- **Every refusal says the same thing.** "I can't do that" is worse than silence for an assistive
  device. The refusal has to name the *reason* — out of reach, gripper full, not homed — which is why
  the phrase table is keyed by condition rather than being a list of strings.

> **CHECK YOURSELF** — List every condition under which the arm currently refuses to move. Your soft
> limits, the homing flag, IK failure, the e-stop latch, an unreachable approach. Does each one have a
> distinct sentence? If two conditions share a phrase, the user cannot tell them apart, and neither can
> you when debugging.

**Capture the broken state.** Two refusals talking over each other, recorded as audio. It is a
five-second clip of a small, unglamorous concurrency bug, and it is the thing that turns 'I added
text to speech' into 'I found out that speech is a shared resource with a queue and a maximum
length'.

### Artifacts

- **`docs/sessions/speak-back/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- The phrase table: every confirmation and every refusal the system can say, and the condition that
  produces it. Kept as data, not scattered through the code.
- **Site:** a video of a refusal — asking for something out of reach and being told why. Every
  portfolio has a success video; almost none has a graceful refusal, and refusals are what
  assistive-technology reviewers look for.
  **The shot:** one clip with **audio**, 10 to 15 seconds — and audio is the specification here,
  because a silent video of a refusal is a video of an arm not moving. Ask for something out of
  reach, let it refuse and say why, with the arm in frame so the refusal is visibly about the arm.

---

## Stage 3 exit gate

1. A spoken instruction reliably produces the right motion.
2. The arm picks up a marked object from a position it was not told about.
3. It refuses impossible requests gracefully **and says why**.
4. The whole pipeline runs locally with the network cable unplugged.

> **PORTFOLIO MOMENT** — Two artifacts here, and both are cheap on the day and impossible to reconstruct
> later. **First: the hand-eye calibration residual.** Record the gripper's miss distance before and
> after M3.3, as two numbers and a scatter plot, into `docs/derivations/hand-eye.md`. "It missed by
> 23 mm in a consistent direction; after solving `AX = XB` it missed by 2 mm in no particular
> direction" is a complete engineering story in one line, and nobody who skipped the step has it.
> **Second: film a failure.** Ask for something out of reach, on camera, and let it refuse and say
> why. Every portfolio has a success video. Almost none has a graceful refusal, and refusals are what
> assistive-technology reviewers actually look for.

**Site artifact:** the end-to-end video, unplugged from the network. That last detail is worth saying
out loud — "no cloud service involved" is a meaningful engineering claim and an assistive-technology
one.

---

# STAGE 4 — THE BIOMECH PAYLOAD

**About ten weeks at hobby pace, four to five at yours. Cost: C$165 — Tier F of *What's Left to Buy*.**

**You will own:** an arm that mirrors your own arm's posture and opens and closes its gripper from
your forearm muscle activity.

---

## Why this stage exists

This is the stage the whole project was aimed at. Everything before it built a machine capable of
being controlled. This is where a human body becomes the controller — which is the definition of the
field you are heading into, and the point where your kinesiology background stops being a footnote on
your resume and becomes the reason you can do this at all.

**Read FIGURE VI.2 before anything else in this stage, and read it as a safety document rather than
as an architecture diagram.** The signal path is the easy part. The line drawn around the battery-
powered island is the part that matters, and M4.2 asks you to redraw it for your own bench before you
attach anything to yourself.

```
FIGURE VI.2 — The EMG chain, and where the isolation barrier actually goes

   YOUR FOREARM
        │  µV-level surface potential
        ▼
 ╭─────────────────────────────────────────────────────────────────────╮
 │  THE ISOLATED ISLAND — battery powered, ONE shared ground, and      │
 │  no electrical path to mains anywhere inside this box.              │
 │                                                                     │
 │  ┌──────────────┐  Ag/AgCl electrodes on a marked elastic band.     │
 │  │  2 signal +  │  Repeatable placement is what makes yesterday's   │
 │  │  1 reference │  model still work today.                          │
 │  └──────┬───────┘                                                   │
 │         ▼                                                           │
 │  ┌──────────────┐  instrumentation amp · band-pass 20–450 Hz        │
 │  │  MyoWare 2.0 │  · rectify · envelope                             │
 │  └──────┬───────┘                                                   │
 │         │  analog envelope. A signal with no shared ground          │
 │         ▼  reference is not a signal at all.                        │
 │  ┌──────────────┐  sample ≥ 1 kHz                                   │
 │  │  MCU + ADC   │  SAME GROUND as the MyoWare, and on the BODY      │
 │  └──────┬───────┘  side of the barrier — never the mains side.      │
 │         │                                                           │
 │         │   ┌───────────────────────┐  powers everything in         │
 │         │   │  battery / power bank │  this box, and nothing        │
 │         │   └───────────────────────┘  outside it                   │
 ╰─────────┼───────────────────────────────────────────────────────────╯
           │  D+ / D− only
 ══════════╪═══════════════════════════════════════════════════════════
      ┌────┴───────────────────────────────────────────────┐
      │  ADuM3160 USB ISOLATOR              NON-NEGOTIABLE │
      │                                                    │
      │  ONLY D+ AND D− CROSS. VBUS and GND do NOT — that  │
      │  is what makes this a barrier rather than a cable. │
      │                                                    │
      │  The part needs power on BOTH sides, and there is  │
      │  no power path between them:                       │
      │     VBUS2 / GND2  ◄── the battery island, above    │
      │     VBUS1 / GND1  ◄── host VBUS, mains side, below │
      │                                                    │
      │  Bridging the battery across to feed both sides is │
      │  the obvious improvisation and it destroys the     │
      │  isolation. Two supplies. Never one.               │
      │                                                    │
      │  It isolates a USB link. It cannot carry an analog │
      │  envelope, which is why it belongs HERE and        │
      │  nowhere else.                                     │
      └────┬───────────────────────────────────────────────┘
 ══════════╪═══════════════════════════════════════════════════════════
           │  D+ / D−
           ▼
    ┌──────────────┐
    │   HOST PC    │  mains-powered, and always on the far side of
    └──────────────┘  the barrier. Its VBUS feeds the isolator's
                      upstream side and stops there.

   THE PROCESSING — runs on the MCU, the host, or both:

                             ┌──────────────┐  M4.3
                        ┌───►│ threshold    │
                        │    │ (crude, and  ├───┐
      ┌──────────────┐  │    │  immediate)  │   │
      │ rectify +    │  │    └──────────────┘   │
      │ smooth (RMS  ├──┤        or             ├───► open(fraction)
      │ over window) │  │    ┌──────────────┐   │     ← S2.10's interface,
      └──────────────┘  │    │ features →   │   │       continuous, not binary
                        └───►│ classifier   ├───┘
                             │ (your data)  │
                             └──────────────┘  M4.4

   Read the branch, not just the boxes. The rectified, smoothed envelope
   feeds BOTH paths — they are alternatives, which is what the 'or' means,
   and both arrive at the same open(fraction). The classifier does NOT sit
   downstream of the threshold: it takes features from the envelope, and you
   could not classify five gestures from a binary decision anyway.

   The window length is the trade-off: longer = smoother and laggier.
   The window is only part of the total delay. Budget ~200 ms END TO END
   — electrode to gripper motion — because above that the lag is
   perceptible to the person wearing it.
```

---

## Start with the software, months early

**You do not need any hardware to begin, and you should not wait.** Public surface EMG datasets exist
precisely for this — the **Ninapro** family is the standard benchmark, recorded from both able-bodied
subjects and amputees performing dozens of distinct movements with research-grade equipment.

Do this during Stage 2's print waits. Arriving at Stage 4 already knowing what a clean EMG signal
looks like removes weeks.

---

## M4.1 · Dataset work, no hardware

**Goal:** a working feature-extraction and classification pipeline on public EMG data, with an
accuracy figure you believe and a cross-subject figure you can explain — all before any electrode
touches you.

**You will be able to:** implement the five standard time-domain EMG features from their definitions, explain why those five dominate the literature, and report within-subject and cross-subject accuracy as two numbers with the gap explained.

Feature extraction, a classifier, cross-validation, an honest accuracy figure.

### The features, and why these five dominate the literature

Raw sEMG is microvolt-scale, bipolar, noisy, and heavily contaminated by mains hum and motion
artifacts. The processing chain — band-pass, rectify, smooth, extract — exists to turn something
nearly unusable into a control signal. Over a sliding window of N samples:

| Feature | Definition | What it captures |
|---|---|---|
| **RMS** | `√( Σxᵢ² / N )` | Amplitude — roughly, effort |
| **MAV** | `Σ\|xᵢ\| / N` | Amplitude, cheaper to compute |
| **Waveform length** | `Σ \|xᵢ₊₁ − xᵢ\|` | Amplitude *and* frequency together |
| **Zero crossings** | count of sign changes (with a noise deadzone) | Frequency content, cheaply |
| **Slope sign changes** | count of direction reversals in the derivative | Frequency content, complementary to ZC |

The last four are the classic Hudgins set, which is what most of the literature means by "time-domain
features"; RMS is the fifth and is nearly interchangeable with MAV. They dominate because they are
cheap enough to run on a microcontroller in real time and they capture nearly all the discriminative
information. That combination is the actual constraint in myoelectric
control.

**Before the window, the sample rate — because it is the one number here that Nyquist decides for
you.** FIGURE VI.2 says sample at ≥ 1 kHz, and that is not a round number picked for comfort:

```
   The band-pass keeps content up to 450 Hz.
   Nyquist says you must sample faster than 2 × 450 = 900 Hz or the content
   above half your sample rate folds back down and appears as LOW-frequency
   signal you cannot distinguish from real muscle activity.

   1 kHz gives you 1.11× over the minimum. That is thin, and it works only
   because the MyoWare's analogue band-pass has ALREADY removed what is
   above 450 Hz before the ADC ever sees it — which is precisely what an
   anti-aliasing filter is for.

   Sample the RAW electrode signal at 1 kHz with no analogue filter in front
   of it and you get mains hum, its harmonics and RF all folded into your
   EMG band, permanently, with no way to remove them afterwards.
```

**That is worth understanding rather than obeying**, because it generalises: any time you digitise
something, the filter in front of the converter is part of the converter. If you ever sample faster —
2 kHz is comfortable and costs nothing on your hardware — do it, and note that it buys you headroom
rather than accuracy.

**Typical window:** 150–200 ms with 50–100 ms overlap. Below ~150 ms the features get noisy, and the
window has to fit inside the ~200 ms end-to-end latency budget from FIGURE VI.2 alongside
classification, transport and the gripper's own travel time — which is why the upper end is 200 and
not the 250–300 you will see quoted for the window in isolation. State the budget and the split in
your write-up; "my window is 200 ms" and "my control lag is 200 ms" are different claims and only one
of them is about what the user feels.

> **WHERE THIS POINTS** — Compute **cross-subject** accuracy as well as within-subject, and notice how
> much worse it is. That gap is one of the central unsolved problems in myoelectric control. Meeting
> it early calibrates your expectations, and being able to discuss it knowledgeably marks you as
> someone who has read the field rather than a tutorial.

### Code — skeleton

```python
# tools/emg_features.py — M4.1
"""Time-domain sEMG features over a sliding window.

Every one of these is two or three lines. Writing them yourself rather than
importing a feature library is the point: you will implement them again on a
microcontroller in M4.3, where there is no library.
"""
import numpy as np

def rms(w):  ...   # TODO  √(Σx²/N)
def mav(w):  ...   # TODO  Σ|x|/N
def wl(w):   ...   # TODO  Σ|x[i+1] − x[i]|

def zc(w, deadzone):
    "" "Zero crossings. The deadzone is not optional — without it, noise
    around zero produces hundreds of spurious crossings and the feature
    measures your amplifier rather than your muscle. TODO: count sign
    changes where BOTH samples are outside the deadzone." ""
    ...

def ssc(w, deadzone):
    "" "Slope sign changes: direction reversals in the first difference,
    with the same deadzone argument and for the same reason." ""
    ...

def window(signal, fs, length_ms, overlap_ms):
    "" "Yield successive windows. TODO: work out the hop in samples from
    length and overlap, and decide what to do with the final partial
    window — dropping it and padding it give different answers and only
    one of them is defensible." ""
    ...
```

**Which classifier**, since "a classifier" is not an instruction. The field's two standard answers are
**LDA** (linear discriminant analysis) and a **linear SVM**, and LDA is the one to start with: it has
no hyperparameters to tune, it trains in milliseconds, it runs in a few multiply-accumulates on a
microcontroller, and it is what a great deal of the myoelectric literature actually uses. Reach for
something heavier only once you have an LDA number to beat — and if a deep model beats it by two
points at fifty times the latency, that is a result worth reporting rather than a reason to switch.

> **CHECK YOURSELF** — Before you train anything: you have five features per channel. With two channels
> that is a ten-dimensional feature vector per window. Roughly how many labelled windows do you need
> before an accuracy figure means anything? You do not need the exact answer — you need to have
> thought about it, because "97 % accurate" on forty windows is not a number.

### Draw this

**The windowing, as a timeline, before you write a line of `window()`.** One horizontal strip of
samples along the page. Under it, draw window one as a bracket; under that, window two, offset by
the hop; under that, window three. Write the length in milliseconds and the hop in milliseconds, and
the number of samples each is at your sample rate.

Two things become visible on that drawing that are invisible in the code, and both are in the
failure list below.

**The overlap is shared data.** Shade the region window one and window two have in common. If those
two windows can land in different folds of your split, you have put nearly the same samples in train
and test — which is exactly how you get an accuracy you should not believe, and it is why the split
is by trial or by session rather than by window.

**The last window does not fit.** Draw it running off the end of the strip. Dropping it and padding
it give different answers and only one is defensible; decide which on the drawing, and write the
reason beside it.

### What will go wrong

- **Accuracy is suspiciously high.** You split windows randomly, and overlapping windows put nearly the
  same data in train and test. Split by trial or by subject, never by window.
- **Zero crossings and slope sign changes are enormous.** No deadzone, so you are counting noise
  crossing zero hundreds of times per window. Both features need one, and choosing it is part of the
  exercise.
- **Cross-subject accuracy is barely above chance.** Expected, and the finding rather than the failure.
  Report it.
- **The features are right and the classifier will not converge.** Feature scales differ by orders of
  magnitude — waveform length is a sum, zero crossings is a count. Standardise before training, and fit
  the scaler on the training fold only.

**Capture the broken state.** Both confusion matrices: the one from the random window split
reporting an accuracy you do not believe, and the one from the split-by-trial that corrects it. Keep
the first. **A suspiciously high number that you then explained** is a stronger artifact than a
defensible number arrived at first time, because it demonstrates the specific scepticism this
milestone is teaching — overlapping windows leak, and the leak is invisible in the metric.

### Artifacts

- **`docs/sessions/emg-features/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- **The confusion matrix**, plus within-subject and cross-subject accuracy as two separate numbers.
  Reporting one number is the thing this milestone exists to stop you doing.
- `tools/emg_features.py` — the five features, implemented and tested against a known signal.
- `docs/decisions/` — window length and overlap, with the latency they imply, tied back to the ~200 ms
  end-to-end budget in FIGURE VI.2.
- **Site:** the confusion matrix and the two accuracy figures with the gap called out. The gap is the
  interesting finding, and saying so is what marks you as having read the field.
  **The shot:** the confusion matrix as a saved figure with class labels readable, and the two
  accuracy figures as text beneath it. Both numbers, always together — the gap is the finding.

---

## M4.2 · Your first real signal, safely

**Goal:** your own EMG on screen, recorded from a correctly isolated bench, with the isolation drawn
and checked before anything was switched on.

**You will be able to:** draw your own isolation topology and check it in three passes before connecting yourself to anything, and recognise mains hum, motion artifact and a bad electrode from the trace alone.

Electrodes on your forearm, MyoWare 2.0, microcontroller on battery **or** behind a USB isolator.
Clean the skin properly. Look at the raw waveform. Clench, release, watch it.

> **WATCH OUT** — **This is the one genuine physical risk in the whole project.** When anything is attached
> to your skin, the microcontroller must be either battery-powered or galvanically isolated from
> mains-powered equipment. **Do both.** The reasoning — that a fault in a mains-connected device can
> put current across your chest through the electrode path — is worth being able to articulate, and
> the medical device world will expect you to have internalised it.
>
> A USB power bank and an ADuM3160-based USB isolator are both in **Tier F** of *What's Left to Buy*,
> budgeted for this stage. Neither was in the Stage 0 order and neither needs to be — but do not
> reach this milestone without them.
>
> **The standard this reasoning comes from is IEC 60601-1**, the general standard for medical
> electrical equipment. You are not certifying anything and you do not need to read it — but knowing
> that the concepts have names is worth an interview answer. The two that matter here: an **applied
> part** is anything that necessarily touches the patient, which is your electrode set; and **leakage
> current** is the small current that flows from mains-powered equipment to earth through everything
> attached to it, which is bounded to microamps for a reason. Battery power removes the mains path
> entirely and galvanic isolation interrupts it. Being able to say "my electrode chain is battery
> powered and the only crossing is an isolated USB link, because the applied part must not become a
> leakage path" is the sentence a medical-device employer is listening for.

### Draw this — and this is the one drawing that could keep you safe

**Draw your own version of FIGURE VI.2, from your own bench, before you stick an electrode to
yourself.** Not a copy of the figure: your actual equipment, with every box labelled and every power
source named. Then check three things on the drawing, in this order.

**One: draw a closed line around everything that runs on the battery.** Electrodes, MyoWare, MCU. If
anything mains-powered is inside that line, or if the line has to be drawn twice because two things
are on different supplies, stop and fix it before you go further.

**Two: trace the ground.** Put your pen on the MyoWare's ground pin and follow it to the ADC's ground
pin without lifting off. If you cannot, the analog signal has no return path and the reading will be
meaningless noise — and if you "fix" that by grounding the MCU to a mains-referenced supply, you have
just built the dangerous version.

**Three: find the single crossing point.** Exactly one thing should cross the barrier, and it should
be the USB cable, and the isolator should be sitting on it. If your drawing has two crossings, one of
them is the fault path.

> **WATCH OUT** — **The commonest way to get this wrong is to put the isolator in the signal path.** It
> looks reasonable: the signal comes off your body, so isolate the signal. It does not work and it is
> not safe. An ADuM3160 isolates a **USB data link** — it carries **D+ and D− across the barrier and
> nothing else** — and it cannot carry an analog envelope at all. Worse, an arrangement that isolates
> between the MyoWare and the ADC leaves the MCU on the mains side of the barrier while your
> electrodes are still wired to a MyoWare that has no shared reference with it. You would have removed
> the signal and kept the hazard.
>
> **The barrier goes on the USB link between the isolated MCU and the mains-powered host, and nowhere
> else.** Everything touching you sits on one battery-powered island with one ground.

> **WATCH OUT** — **VBUS does not cross the barrier, and the isolator needs its own supply on each
> side.** This is the detail that most often gets built wrong, because the part's pinout invites it.
> The ADuM3160 has `VBUS1`/`GND1` and `VBUS2`/`GND2` — those are **two separate per-side supplies with
> no power path between them**, not a pass-through. Feed the peripheral side (`VBUS2`/`GND2`) from
> your battery island, and the upstream side (`VBUS1`/`GND1`) from the host's own USB VBUS, which
> stays on the mains side. **If VBUS or GND crossed, there would be no barrier** — that is the whole
> mechanism, and it is why the figure draws only D+ and D− going through.
>
> The improvisation to refuse: powering both sides from the battery because it is right there and the
> upstream side is not lighting up. That single wire re-joins the two grounds and puts you back in
> the situation the isolator exists to prevent. If the upstream side is unpowered, the host is not
> supplying VBUS — check the cable and the port, not the barrier.

### What will go wrong

- **The trace is a flat line, or pinned to a rail.** Skin preparation, nine times out of ten. Clean
  with alcohol, let it dry fully, and check the reference electrode is on bone or an inactive site —
  not on the same muscle belly as the signal pair.
- **A clean 50 or 60 Hz sine dominates everything.** Mains hum, coupled capacitively. It is the single
  most common sEMG artifact and it is also a diagnostic: if it *increases* when you touch the laptop,
  your isolation is not doing what you think it is.
- **Large, slow swings when you move your arm.** Motion artifact from the electrode–skin interface,
  not muscle. It lives below about 20 Hz, which is exactly why the band-pass starts there.
- **The envelope responds but with a lag you can feel.** Your smoothing window is too long. This is the
  trade-off named in FIGURE VI.2 and it is the number to tune first.
- **It worked yesterday and the thresholds are all wrong today.** Electrode placement moved. That is
  M4.4's whole problem, arriving early.

**Capture the broken state.** A clean 50 or 60 Hz sine swamping the EMG trace. Screenshot it. It is
the single most common sEMG artifact, it is instantly recognisable to anyone who has recorded a
biosignal, and it doubles as a diagnostic — if it grows when you touch the laptop, your isolation is
not doing what you believe it is, and **that is worth knowing before you trust the rest of the
stage**.

### Prove it

> **CHECK YOURSELF** — Before you record: sEMG is microvolt-scale at the skin and your ADC reads volts.
> Roughly what gain sits between them, and what would the envelope read at rest if that gain were right?
> You do not need a precise answer — you need to know whether a flat line at rest is the amplifier
> working or the electrode not connected, and those look identical without a number in mind.

Record thirty seconds: ten seconds relaxed, ten seconds at a light clench, ten seconds at a hard
clench. Plot the raw signal and the envelope on the same axes. You should be able to point at the
three regimes without a label. **Then repeat the whole recording tomorrow, from a fresh electrode
application, and overlay the two envelopes.** The gap between them is the cross-session problem you
will spend M4.4 on, and measuring it on day one means you are not surprised by it later.

### Artifacts

- **`docs/sessions/first-emg-signal/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- **Your own hand-drawn version of FIGURE VI.2**, photographed — the isolated island outlined, the
  ground traced, the single barrier crossing marked. This is a safety artifact and it is dated
  evidence that you reasoned about it before you connected yourself to anything.
- **The three-regime recording** — relaxed / light / hard — raw and envelope on the same axes.
- **The day-two overlay** from a fresh electrode application, and the gap between the two envelopes
  quoted as a number.
- `docs/decisions/` — battery, isolator, or both, and the reasoning in one paragraph you could say out
  loud in an interview.
- **Site:** the three-regime plot. It is the first evidence that a human body is in the loop.
  **The shot:** the three-regime plot as one figure: raw and envelope on shared axes, with the
  three regions labelled on the plot itself rather than described underneath. A reader should be
  able to point at relaxed, light and hard without reading a word.

---

## M4.3 · Threshold control

**Goal:** your muscle opens and closes the gripper through S2.10's `open(fraction)` interface — and
you have felt why a fixed threshold is not enough.

**You will be able to:** drive a continuous interface from a biosignal envelope, and explain from your own fatigue plot why a fixed threshold is not enough — using median frequency, not just amplitude.

Rectify, smooth, threshold, and drive the `open(fraction)` interface you defined in **S2.10** —
which, being continuous rather than binary, is already the right shape for M4.4's classifier output.
Crude, immediate, enormously satisfying.

It also teaches you why crude is not enough: **the threshold that works when you are rested does not
work when you are fatigued.** Muscle fatigue shifts both the amplitude and the frequency content of
the signal — median frequency drops as fatigue accumulates, which is itself a measurable thing and a
nice piece of kinesiology to bring into an engineering project.

### Draw this

**One envelope trace with both thresholds drawn across it, and the output underneath.** Sketch a
plausible envelope — rising into a clench, wobbling near the top, falling away — then draw the open
threshold as one horizontal line and the close threshold as a *lower* one. Below it, on the same
time axis, draw the resulting gripper state as a square wave.

Then draw the same envelope again with a **single** threshold and watch the square wave chatter
where the signal wobbles across it. That pair is the entire argument for hysteresis, it takes four
minutes, and it is a great deal more convincing than the two-line definition in *Before You Build*.

Finally, on the first drawing, sketch the baseline creeping upward as you fatigue and mark where the
lower threshold stops being crossed. That mark is the failure at the top of the list below, and it
is why M4.4 exists.

### What will go wrong

- **It works for a minute and then the gripper sits half closed.** Fatigue: your baseline has drifted up
  and the threshold no longer means what it did. The milestone's whole lesson, arriving early.
- **It chatters at the boundary.** No hysteresis. One threshold to open, a lower one to close — this is
  the first place in the project you need it.
- **The gripper twitches whenever you move your arm.** Motion artifact below 20 Hz getting through, or a
  cable tugging the electrode. Check the band-pass and the strain relief before the software.
- **The response feels laggy and the envelope looks fine.** Your smoothing window is doing what you
  asked. Budget the whole chain — FIGURE VI.2's 200 ms is end to end, not window length.

**Capture the broken state.** The gripper sitting half closed after a minute of use, with your
baseline drifted up underneath it. Film it. The whole argument for M4.4 is that a fixed threshold
fails, and a clip of a gripper that will neither open nor close while you are still trying makes it
in about four seconds.

### Artifacts

- **`docs/sessions/threshold-control/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- A video of the gripper opening and closing from your forearm. Short, and the most immediately
  legible thing in Stage 4.
- **The fatigue plot**: the same threshold, applied to a fresh recording and to one taken after two
  minutes of sustained effort, with the median frequency of each. That plot is the argument for M4.4
  and it is a piece of kinesiology most engineers cannot produce.
- `docs/decisions/` — threshold value, smoothing window, and the hysteresis you needed to stop it
  chattering at the boundary.
- **Site:** the fatigue plot. A threshold that works rested and fails tired, with the median frequency
  of each recording beside it — that is a piece of kinesiology most engineers cannot produce, and it is
  the argument for everything M4.4 does.
  **The shot:** the fatigue plot as one figure, both recordings on shared axes, with the threshold
  drawn as a horizontal line across both and the median frequency of each printed on the plot. The
  line crossing one trace and not the other is the argument.

> **CHECK YOURSELF** — Predict, before you record it: after two minutes of sustained effort, does your
> envelope amplitude go *up* or *down* at the same felt effort, and which way does median frequency
> move? One of those two is counter-intuitive, and getting it wrong is the most instructive possible
> way to meet muscle fatigue.

---

## M4.4 · Your own classifier, on your own signal

**Goal:** a gesture classifier trained on your own recordings that still works tomorrow, with
within-session and cross-session accuracy reported separately.

**You will be able to:** explain why a model trained today fails tomorrow, quantify it as a cross-session accuracy gap, and describe the engineering — not the algorithm — that narrows it.

Record your own gesture data with consistent electrode placement. Train. Run inference. Map gestures
to grip commands.

**Repeatable electrode placement is what makes yesterday's model still work today.** An elastic band
with marked positions is a legitimate engineering solution, not a hack — it is what the commercial
devices do.

Report **within-session** and **cross-session** accuracy separately, and be honest about the gap. The
gap is the interesting finding, not a flaw in your work.

**Record both numbers, and the session dates they came from, the moment you have them.** Electrode
placement, skin condition and how tired you were all move these figures, so an accuracy quoted
without its dates is a number nobody can interpret — including you, next month, when you are trying
to work out whether a change helped.

> **CHECK YOURSELF** — Predict the size of that gap in percentage points before you measure it, using
> M4.1's cross-subject number as your anchor. Cross-*session* on one person should sit between
> within-session and cross-subject. If yours does not, something is wrong with how you split the data,
> and that is worth finding before you report anything.

### Draw this

**The electrode band, to scale, as the drawing you will need to reproduce.** The forearm in
cross-section, the two signal electrodes and the reference marked on it with their distances from a
bony landmark you can find again — the ulnar styloid is the usual one — and the inter-electrode
spacing written on the page.

**This is a drawing whose value is entirely in being repeatable.** The band with marked positions is
the actual engineering in this milestone; the classifier is a library call. A drawing that lets you
place electrodes the same way in three weeks is what makes the cross-session number a measurement of
your model rather than of your memory.

Then, beside it, sketch the confusion matrix you *expect* — which gestures you think will be
confused with which, and why, in terms of which muscles are under which electrode. Checking that
prediction against the real matrix is worth more than the accuracy figure, because a matrix that
confuses the pairs you predicted is a model behaving understandably, and one that does not means
something else is going on.

### What will go wrong

- **Within-session accuracy is 98 % and cross-session is 60 %.** The expected result, the central
  unsolved problem of the field, and reporting it honestly is the milestone.
- **Accuracy collapses when you sit differently.** Limb position effect: the same gesture produces
  different sEMG at different arm angles. Record training data at more than one posture.
- **One gesture is never predicted.** Class imbalance, or two gestures genuinely indistinguishable at
  your electrode placement. The confusion matrix tells you which; a single accuracy number does not.
- **The model is perfect and you trained and tested on the same session.** Split by *session*, not
  randomly across windows — windows overlap, so a random split leaks.

**Capture the broken state.** The cross-session confusion matrix, next to the within-session one.
**Publish both.** This is the milestone where the failure is the finding: 98 % on one afternoon
against 60 % across three days is the central unsolved problem of myoelectric control, honestly
measured on your own arm, and reporting only the first number is the thing this milestone exists to
stop you doing.

### Artifacts

- **`docs/sessions/gesture-classifier/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- **Your own dataset**, recorded across at least three separate electrode applications on different
  days, committed (or its collection scripts, if it is large).
- **Within-session and cross-session accuracy, side by side**, with the gap stated and explained.
- A photograph of the marked elastic band. Repeatable placement is the actual engineering here, and it
  photographs better than the classifier does.
- **Site:** the two accuracy figures and one sentence on why they differ. This is the paragraph that
  says you understand myoelectric control rather than scikit-learn.
  **The shot:** both confusion matrices side by side at the same colour scale, with the two
  accuracy figures and one sentence on why they differ. Same colour scale or the comparison lies.

---

## M4.5 · Wearable IMUs and your own sensor fusion

**Goal:** shoulder and elbow angles estimated from two raw six-axis IMUs, by a complementary filter
and then a Kalman filter you wrote, with the two compared on the same recording.

**You will be able to:** write a complementary filter and say why it works as a high-pass plus a low-pass summing to unity, then say precisely what a Kalman filter estimates that you were previously guessing.

Two inertial sensors, one on the upper arm and one on the forearm. Write a **complementary filter**,
then a **Kalman filter**, and compare them.

### The complementary filter, in one line

```
θ = α · (θ_prev + ω_gyro · dt)  +  (1 − α) · θ_accel        with α ≈ 0.98
```

It trusts the gyroscope short-term (accurate but drifts) and the accelerometer long-term (noisy but
absolute). One tunable parameter, four lines of code, and it works. Understanding *why* it works —
that it is a first-order high-pass on one signal and a low-pass on the other, summing to unity — is
the point.

Then do the Kalman filter properly and compare. The Kalman filter is what you get when you stop
guessing `α` and start estimating it from a model of the noise.

> **CHECK YOURSELF** — Work out the complementary filter's time constant at α = 0.98 and your sample
> rate, in seconds, before you run it. Then answer: is that faster or slower than your arm moves during
> a normal reach? If it is slower, the filter will lag visibly and you will be tempted to blame the
> IMU.

> **WATCH OUT** — Use **raw six-axis** IMUs, not chips that fuse internally. The fusion is the skill you
> are here for, and buying a part that does it for you removes the exercise. This is explicitly why
> the parts document specifies raw parts.

**Quaternions** land here too: composing rotations without gimbal lock. Your MPU6050 from the starter
kit is enough to begin.

### Draw this

**The complementary filter as two filters summing to unity, in your own handwriting.** This is
listed in the artifacts as a derivation and it is four lines of algebra, so do it as algebra rather
than as a block diagram: start from `θ = α·(θ_prev + ω·dt) + (1 − α)·θ_accel`, and show that the
gyro path is a first-order high-pass and the accelerometer path is the complementary low-pass, and
that the two transfer functions add to one at every frequency.

**That last property is the whole reason it works** and the reason for the name, and it is the
difference between using the filter and understanding it.

Then, on the same page, draw the two error sources as sketches rather than equations: gyro drift as
a slow ramp away from truth, accelerometer noise as fast scatter around it. Mark on the frequency
axis where α puts the crossover, and write its time constant in seconds beside it.

> **CHECK YOURSELF** — From that page: if you doubled your sample rate and left α alone, would the
> crossover move? Answer from the time constant rather than from intuition. It is the same question
> as Stage 0 S10's filter, and getting it wrong is how α becomes a magic number again.

### What will go wrong

- **The estimate drifts steadily.** Gyro bias — it is not zero at rest, and integrating it integrates
  the bias too. Measure it while the sensor is still and subtract it; that measurement is itself a
  deliverable.
- **The angle is right until you move fast, then it jumps.** The accelerometer is measuring your
  acceleration as well as gravity, and the filter trusts it. That is exactly what α trades, and it is
  why the Kalman version exists.
- **α = 0.98 is copied and never justified.** Work out its time constant at your sample rate and check
  it against how fast your arm actually moves. One line of arithmetic, and it turns a magic number into
  a choice.
- **Two IMUs on one I²C bus and only one answers.** Address collision, exactly as with the AS5600s.
  MPU6050 has one address-select pin, so two is fine — three is not.

**Capture the broken state.** The estimate drifting steadily away from truth before you measure and
subtract the gyro bias. Save the plot. A slow, perfectly linear drift is a beautifully diagnostic
shape — it says integration and it says constant offset — and putting it next to the corrected trace
shows a bias measurement doing exactly one job.

### Artifacts

- **`docs/sessions/imu-fusion/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- **The complementary filter and the Kalman filter, plotted on the same recording**, against a known
  reference angle. One figure, two estimators, and the differences visible.
- `docs/derivations/` — the complementary filter written out as a high-pass plus a low-pass summing to
  unity, in your handwriting. It is four lines of algebra and it is what turns α from a magic number
  into a choice.
- `docs/decisions/` — your α, and the drift-versus-noise trade it represents.
- **Site:** the two-estimator overlay. Comparing your own filters is a much stronger claim than
  running one.
  **The shot:** one figure, both estimators and the reference angle on shared axes, with a legend.
  Zoom to a window where they visibly disagree rather than showing a minute in which they overlap.

---

## M4.6 · Mirroring

**Goal:** the arm follows your arm — posture from the IMUs, grip from your muscles, end to end,
without a keyboard.

**You will be able to:** close a loop from a human limb to a machine limb and quote its end-to-end latency as a measured number against a stated budget.

Your shoulder and elbow angles, estimated from the fused IMU data, become the arm's joint targets. It
follows you.

Combined with M4.4 you now have **posture from your limb and grip from your muscles** — which is, in
miniature, the control scheme of a myoelectric prosthesis.

### Draw this

**The latency budget, as a stacked bar, before you measure it.** One horizontal bar with a 200 ms mark
on it, divided into every stage the signal passes through, each drawn to the width you *predict*:

```
   electrode → envelope     the MyoWare's own analogue smoothing
   → feature window         150–200 ms, and it is the obvious suspect
   → classification         your model's inference time
   → transport              host → gateway → CAN → joint
   → joint control loop     1 ms, and it is not the problem
   → gripper travel         the servo physically moving, which people forget
```

Predict each width, total them, and see whether your prediction even fits inside 200 ms before you
build it. **Then measure and redraw the bar with the real numbers beside your guesses.**

The value is in which stage turns out to dominate. Almost everyone assumes it is the model; it is
usually the window plus the mechanical travel, neither of which is code. Being wrong about that on
paper costs nothing and being wrong about it while optimising the wrong thing costs a weekend.

### Artifacts

- **`docs/sessions/mirroring/README.md`** — written at the end of the session, not the
  start. Three to five bullets on what actually happened, what the objective did not predict,
  and what you got wrong first. See [the template](../sessions/_TEMPLATE.md).
- **The mirroring video** — your arm and the machine's, in one frame, moving together. This is the
  artifact the whole project was aimed at and it should be the first thing on the site.
- A latency measurement: your movement to the arm's movement, in milliseconds, measured off the video
  or off a synchronised log. Quote it against the ~200 ms budget from FIGURE VI.2.

> **CHECK YOURSELF** — Before you measure it, budget it: add up every stage you built — EMG window,
> classification, transport, CAN, the joint's own loop, and the gripper's mechanical travel. Which one
> dominates? Then measure, and see whether you were right. Being wrong about which stage owns your
> latency is the normal outcome and it is exactly the thing worth knowing.
- A recorded bag of one full session — IMU, EMG, joint states and commands together — which is also
  the substrate for the learning-from-demonstration extension in the Guide's Appendix E.
- **Site:** the mirroring video, and the latency number under it.
  **The shot:** one clip, 20 to 40 seconds, landscape, **your arm and the machine's arm in the
  same frame** — this is the artifact the whole project aimed at and split-screen from two
  recordings does not carry it. One camera, both arms, one take. The measured latency goes under
  it as text.

---

## Stage 4 exit gate

1. You can explain your EMG processing chain from electrode to decision.
2. A trained classifier works across sessions on different days.
3. The arm mirrors your posture with a filter you wrote and can explain.
4. You can state your within-session and cross-session accuracy **and why the gap exists**.
5. The whole thing runs end to end without you touching a keyboard.

> **WATCH OUT** — **Nothing here is a medical device and nothing here should be used as one.** Mimic is a
> learning platform. Keeping that boundary explicit — in your README, in conversation, in your own
> head — is part of behaving correctly in this field, and stating it unprompted in an interview reads
> as maturity rather than hedging.

---

# STAGE 5 — IMPEDANCE AND REHAB MODE

**Open-ended. Cost: minimal — mostly software on hardware you already have.**

**You will own:** an arm that is compliant rather than stiff, and can guide, assist, or resist a human
hand.

---

## Why this is the highest-value optional stage for you

Every controller so far has been a **position** controller: the arm goes where it is told and resists
being moved. That is exactly wrong for anything that physically contacts a person.

Impedance control is the answer, and it is the concept that turns Mimic from "a robot arm" into "a
device that could plausibly do therapy" — a meaningfully different portfolio story for the companies
you are targeting.

**FIGURE VI.3** puts the two side by side. The difference that matters is not the equation; it is that
the right-hand column commands **current** and reads **force**, where the left commands duty and reads
only position. Everything else in this stage follows from that one change.

```
FIGURE VI.3 — Position control versus impedance control

      POSITION CONTROL (Stages 0–3)   IMPEDANCE CONTROL (Stage 5)
  
        x_target                           x_target
            │                                  │
            ▼                                  ▼
      ┌───────────┐                   ╔═════════════════╗
      │    PID    │◄────┐             ║  virtual        ║◄────┐
      └─────┬─────┘     │             ║  spring K       ║     │
            │ duty      │             ║  + damper B     ║     │
            ▼           │             ║  + mass M       ║     │
       [ motor ]        │             ╚════════┬════════╝     │
            │           │                      │ FORCE        │
            ▼           │                      ▼              │
      ●═══ arm ═══      │                 τ = Jᵀ · F          │
            │           │                      │ current      │
            ▼           │                      ▼              │
      [ encoder ]───────┘                ●═══ arm ═══         │
       position                                │              │
                                               ▼              │
                                         [ encoder ]──────────┤
                                          position            │
                                                              │
                                         [ INA219 ]           │
                                               │ current      │
                                               ▼              │
                                          τ ≈ Kt · I          │
                                      [ F_tip = J⁻ᵀ·τ ]───────┘

   BOTH LOOPS ARE CLOSED, and that is the thing to read. Follow the right-hand
   line from the arm all the way back up to the virtual spring: position comes
   back from the encoder, and force comes back from current through Kt and the
   inverse-transpose Jacobian. A spring needs to know how hard you are pushing
   it, so if that second return path is missing you have not built impedance
   control — you have built position control with extra steps.

   The other difference: the left column commands DUTY and the right commands
   CURRENT. Note that your driver takes a duty cycle, not a current, so
   "command current" means closing a small current loop of your own around the
   INA219 reading. Nothing earlier in this project builds one. That is real
   work and it is the first thing Stage 5 asks you to write.

   current → torque → FORCE. The last arrow is the one people leave out.

   F = M·(ẍ_t − ẍ) + B·(ẋ_t − ẋ) + K·(x_t − x)

   K large, B large  →  stiff. Behaves like position control.
   K → 0             →  limp. Follows your hand (gravity comp only).
   K moderate        →  guides, assists, resists. The therapy behaviour.

   THE HARD PART IS MECHANICAL, NOT SOFTWARE: a 270:1 gearbox is barely
   backdrivable, so the joint resists being moved no matter what the maths
   says. Read the backdrivability caution before committing to this stage.
```

> **DEFINITION** — **Impedance control** commands a *relationship* between position and force rather than a
> position. You specify a virtual stiffness `K`, damping `B`, and mass `M`, and the endpoint behaves
> as though attached to its target by a spring and damper with those properties. The full relation is
> the first block below; the form you will actually code is the second.

```
full           F = M·(ẍ_target − ẍ)  +  B·(ẋ_target − ẋ)  +  K·(x_target − x)

what you code  F = K·(x_target − x)  −  B·ẋ
```

In practice you implement the two right-hand terms and leave `M` at zero — commanding a virtual mass
needs acceleration feedback you do not have, and the spring-damper is the useful part. Against a
stationary target (`ẋ_target = 0`) the full relation collapses to exactly the second line, which is
worth doing on paper once so the simplification is a result rather than a shortcut.

> **DEFINITION, continued** — Low `K` gives you an arm you can push around. High `K` approaches
> position control. The whole spectrum from "rigid robot" to "soft assistant" is one number.

---

## What to build, in order

### 1 · Current-based force estimation — and the current loop underneath it

Motor current is roughly proportional to torque. With the **INA219 already on each joint** you can
estimate endpoint force with no force sensor at all.

**But note what "command current" actually requires**, because FIGURE VI.3 says it and nothing earlier
in this project builds it. Your driver takes a **duty cycle**, not a current. Between "I want 0.4 A"
and the hardware there has to be a small feedback loop of your own:

```
   desired current  ──►(Σ)──► PI ──► duty ──► [ driver ] ──► motor
                        −▲                                     │
                         └──────────── [ INA219 ] ◄────────────┘
```

That is a second control loop, nested inside the impedance loop, and it has all the same properties
you spent Stage 0 learning: it needs a rate, it needs gains, it saturates, and it winds up. Two things
make it harder than the position loop rather than easier:

- **The INA219 is slow.** It is an I²C part with a conversion time measured in hundreds of
  microseconds to milliseconds depending on its averaging settings, so your current loop runs far
  slower than your 1 kHz position loop. Look up its conversion-time table and let that number set the
  rate rather than choosing one.
- **PWM makes the current a triangle wave, not a constant.** What you measure depends on *when* in the
  PWM cycle you sample. Averaging over several PWM periods is the practical answer, and it costs you
  bandwidth.

Build it as its own thing, prove it in isolation — command 0.2 A, measure 0.2 A — and only then put
the impedance maths on top. This is the two-fronts rule again, and it is the reason this section is
first in the list rather than the force estimate being treated as a free consequence of owning a
current sensor.

```
τ_motor ≈ Kt · I          (Kt from your own measurement, not a datasheet)
τ_joint = τ_motor · N · η (gear ratio × gearbox efficiency — η is well under 1 and
                           you must measure it, not assume it)
F_tip   = J⁻ᵀ · τ         (the INVERSE transpose maps joint torques to tip forces;
                           the plain transpose maps forces the other way — see below)
```

> **DEFINITION** — **The torque constant, `Kt`.** The proportionality between current through a DC motor's
> winding and the torque it produces, in newton-metres per amp. It is the single number that makes
> current usable as a force sensor, and for a brushed motor it is also numerically equal to the back-
> EMF constant `Ke` in SI units — which is the easier way to measure it: spin the motor at a known
> speed, measure the voltage it generates, and `Ke = V / ω`. Do that rather than trusting a listing,
> for the same reason you measured everything else on these motors: the part number does not identify
> the part.
>
> The chain above then reads left to right as **current → motor torque → joint torque → tip force**,
> and each arrow has an error term. `Kt` is the cleanest; `η` is the worst, because gearbox friction
> varies with load, direction and temperature and a single efficiency number cannot represent it.
>
> **`J⁻ᵀ` is the inverse transpose of the Jacobian you derived in S2.3** — the same 2×2 matrix, doing
> its third job. `τ = Jᵀ · F` converts a desired tip force into joint torques, which is what you
> command; running it backwards converts measured joint torques into an estimated tip force, which is
> what you sense. Note that it is singular in exactly the same configurations, so your force estimate
> degrades near full extension for precisely the reason your velocity control did.

Crude — gearbox friction is significant at high ratios and is not captured by a single efficiency
number, since it varies with load and direction — but sufficient and free. Characterise the friction
by measuring current at constant velocity with no load, in both directions, and subtract it.

### Draw this — the two nested loops, because this is where people lose the thread

**One page, two loops, one inside the other.** Stage 5 is the first time in this project that a control
loop contains another control loop, and the drawing is what makes that legible.

Draw the **outer** loop first: desired position → the virtual spring and damper → desired force →
`τ = Jᵀ·F` → desired *torque*. Stop there and put a box around everything so far, labelled "impedance,
runs at your control rate".

Now draw the **inner** loop inside the arrow that leaves that box: desired torque → divide by `Kt` →
desired **current** → a summing junction → a small PI controller → **duty** → driver → motor. Feed the
INA219's measured current back to that junction. Label the box "current loop, runs at whatever the
INA219 can actually sample at".

Then mark the three things that make it a real drawing rather than a diagram:

1. **The two rates, written on the two boxes.** They are not the same and the inner one is slower,
   which is the opposite of what a beginner expects and it is the constraint the whole stage lives
   under.
2. **Where `Kt` and `η` enter**, and which of them you measured and which you assumed.
3. **The one signal that leaves the inner loop and returns to the outer** — the measured current,
   which becomes your estimated tip force through `J⁻ᵀ`. That is the arrow FIGURE VI.3 says people
   leave out, and on your own drawing you will see immediately whether you have drawn it.

> **CHECK YOURSELF** — An inner loop that is slower than the loop wrapped around it is normally a
> stability problem. Say, in one sentence, why this arrangement is still usable — and what you would
> have to do to the outer loop's gains if the INA219 turned out to be slower than you hoped. The answer
> is the same idea as the derivative filter's phase lag in Stage 0 S10, one level up.

### 2 · Gravity compensation

Compute the torque needed to hold the arm's own weight at any pose and apply it **feedforward**. You
already derived this in Stage 2's torque budget — the same expression, evaluated continuously at the
current angles rather than at worst case.

The arm becomes weightless in your hand. It is a striking demonstration and a prerequisite for
everything else here.

> **PORTFOLIO MOMENT** — **Film this one, and film it the day it works.** Thirty seconds of your hand
> moving a powered arm around as though it were weightless, then the same arm rigid with compensation
> off, is the single most legible artifact in the entire project — it needs no explanation, no plot
> and no domain knowledge to be impressive, and it is the clearest possible evidence of the
> medical-robotics story you are telling. It also cannot be reshot later: it depends on a gravity
> model tuned to a specific arm on a specific day, and the moment you change a link or a motor it is
> gone. Straight into the website repository, and put it at the top of the site.

### 3 · Virtual constraints

A software wall the endpoint cannot cross, or a groove it is guided along. This is the mechanism
behind guided rehabilitation exercises — and behind surgical robot safety boundaries.

### 4 · Assistive and resistive modes

Help the user complete a movement, or oppose it for strength training. Adjust assistance based on
measured performance — which is where your kinesiology background gives you something to say that
most engineers cannot.

> **WHERE THIS POINTS** — Upper-limb rehabilitation robots are frequently planar two-degree-of-freedom
> machines, for exactly the reasons that made this a good learning geometry: tractable kinematics, a
> tabletop workspace, and a human interacting with the endpoint. If any part of your future work heads
> toward therapy devices, exoskeletons, or anything sharing physical space with a person, impedance
> control is the foundational concept — and having implemented it, however crudely, on hardware you
> built is genuinely distinguishing.

---

## A caution about backdrivability

Your gearboxes are the obstacle here, and it is worth knowing before you are disappointed.

A reduction of a few hundred to one is **not backdrivable** — you cannot push the output shaft and
turn the motor, because the friction reflected through that ratio swamps the input. (Whatever ratio
you measured in Stage 0 S3, and whatever you moved to in Stage 2, this holds for all of them.) Impedance control on a
non-backdrivable joint is possible but limited: you are simulating compliance through the controller
against a mechanism that is fighting you, and the achievable stiffness range is narrow.

The real answer, if you pursue this seriously, is **lower gear ratios and higher-torque motors** — and
ultimately brushless motors with field-oriented control, which is what every serious compliant robot
uses. That is a substantial firmware project in its own right and Appendix E of the Project Guide
lists it as a natural extension.

Do the crude version first. Knowing *why* it is limited is worth as much as the implementation.

### What will go wrong

- **Gravity compensation over- or under-shoots and the arm drifts.** Your mass model is the assumed
  one from S2.4 rather than the measured one from S2.9. Gravity compensation is the first thing in the
  project that is sensitive to those masses being *right* rather than approximately right.
- **The force estimate is dominated by friction, not by load.** Expected at these gear ratios.
  Characterise it: drive each joint at constant velocity with no payload, in both directions, record
  the current, and subtract that baseline. The difference between the two directions is itself a
  measurement of the friction you cannot model.
- **The arm feels compliant in one direction and rigid in the other.** That asymmetry is the gearbox,
  not your controller. It is the clearest possible demonstration of why backdrivability is a
  mechanical property.
- **Raising `K` makes it oscillate before it makes it stiff.** You have hit the stability limit set by
  your sample rate and the sensing lag. This is Stage 0's `Ku` experiment again, in a different
  coordinate system, and the fix is the same: more damping `B`, or a faster loop.
- **It works with the arm still and misbehaves the moment you move it fast.** You left `M` at zero and
  the inertia is not negligible at speed. That is a known limitation, not a bug — say so rather than
  chasing it.

**Capture the broken state.** Your hand-drawn latency bar with the predicted widths on it,
photographed **before** you measure. The measured bar is the result; the prediction beside it is the
interesting part, because almost everybody guesses the model dominates and it is almost always the
feature window plus the gripper's mechanical travel. A wrong prediction you committed to in ink is
worth more here than a right one.

**Capture the broken state.** The arm feeling compliant when pushed one way and rigid the other.
Film your hand pushing it in both directions in one take. **That asymmetry is the gearbox, not your
controller**, and it is the clearest demonstration available that backdrivability is a mechanical
property you cannot code around — which is the honest limitation of this whole stage and a better
thing to be able to show than a stiffness that happened to work.

### Prove it

Two plots from the same rig. First, gravity compensation off versus on: the current drawn while
holding the same pose, showing the feedforward term doing the work. Second, an interaction plot —
push the endpoint with your hand and record commanded force against measured displacement. The slope
of that line is your achieved stiffness, in newtons per metre, and it should match the `K` you asked
for. Where it does not, the gap is friction, and you can quote it as a number.

### Artifacts

- **`docs/sessions/impedance-control/README.md`** — written at the end, not the start. Three to five
  bullets on what actually happened, what the objective did not predict, and what you got wrong
  first. See [the template](../sessions/_TEMPLATE.md). This stage is open-ended and unnumbered, so
  it gets one folder rather than one per sub-step.
- The two plots above, and your measured `Kt` with the method you used to get it.
- `docs/derivations/` — the two nested loops, drawn, with the two rates on the two boxes.
- **Site:** the gravity compensation clip, and it belongs at the top of the site rather than at the
  end of it.
  **The shot:** one clip, about 30 seconds, one take, landscape. Your hand moving the powered arm as
  though it weighed nothing, then the same arm rigid with compensation switched off — **both halves
  in the single take**, because the cut is what a viewer would otherwise assume you were hiding.
  Your hand and the whole arm in frame throughout. It needs no plot, no caption and no domain
  knowledge to land, and **you cannot reshoot it**: it depends on a gravity model fitted to a
  specific arm on a specific day, and it is gone the moment you change a link or a motor.

---

# Writing the sessions when you get there

When you reach each stage, turn its milestones into sessions the same way Stages 0 to 2 are
structured: goal, concept with an analogy, math you derive, a diagram you draw, the build, code
skeletons, what will go wrong, the test, the artifacts.

Two things will have changed by then and are worth checking rather than assuming:

- **The speech and language tooling.** Check what is current in the ROS 2 ecosystem rather than
  trusting a package name from a document written months earlier. As a starting point: `whisper_ros`
  and `llama_ros` by mgonzs13 are the established packages, they track ROS 2 distributions on
  separate branches, and `chatbot_ros` combines them — that is the whole M3.5 → M3.6 → M3.7 chain off
  the shelf, with `piper_ros` covering the speech synthesis in M3.7. **Check the repository's branch
  list for the distribution you are on before you install anything**, because that branch list is the
  authoritative statement of what is supported and it changes.
- **Your own arm.** Stage 3 onward depends on link lengths, gripper design, and camera mount that do
  not exist yet. Sessions written now would be about a robot you have not built.

The mathematics in this volume — the pinhole model, the EMG features, the complementary filter, the
impedance relation — does not go stale. That is the part worth having written down early.

---

## Figure index

Every figure in this document is plain ASCII/box-drawing art inside a fenced code
block, tagged `FIGURE <id> — <title>` on its first line. That is deliberate: it
renders correctly in GitHub and in any Markdown viewer, and it stays diffable in
Git. For a PDF export, set the monospace font to one with full box-drawing and
half-block coverage — **DejaVu Sans Mono** is the usual answer; the core PDF
monospace fonts do not carry the geometric and box-drawing characters these figures use — in this
volume: `╭ ╮ ╰ ╯ ═ ║ ╔ ╗ ╚ ╝ ╪ ◄ ► ▼ ← → ≈ ≥ · ●` — and will drop or substitute them.

| Figure | Title | Where |
|---|---|---|
| **VI.1** | The Stage 3 pipeline, and where each milestone sits | Stage 3 — Why this stage exists |
| **VI.2** | The EMG chain, and where the isolation barrier actually goes | Stage 4 — Why this stage exists |
| **VI.3** | Position control versus impedance control | Why this is the highest-value optional stage for you |
