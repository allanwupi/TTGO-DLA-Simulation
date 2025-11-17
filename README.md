Diffusion-limited aggregation (DLA) simulation
===

Simulate randomly walking particles and growth of Brownian trees on the T-Display S3.

Inspirations and References
---

- Project initially inspired by [this Youtube video](https://www.youtube.com/watch?v=gsJHzBTPG0Y) about procedural mountain generation.
- See the [Wikipedia article on DLA](https://en.wikipedia.org/wiki/Diffusion-limited_aggregation) for more details.
- There are some excellent animations on [this page about cellular automata](https://robotmoon.com/cellular-automata/#elementary-cellular-automata).

![Example Brownian tree.](https://github.com/allanwupi/TTGO-DLA-Simulation/blob/main/img/IMG_0146.jpg)

Simulation Overview
---

1. Place seed at the centre of the screen
2. Spawn particle on circular perimeter: random angle and initial radius 3
3. Walk particle randomly until it sticks to the seed (Moore neighbourhood)
4. Respawn particle and repeat - increase spawn circle radius when necessary
5. Once circle radius exceeds screen width, spawn randomly outside radius instead
6. Stop simulation after a set number of particles have aggregated (default: 4000)

User Interface
---

- Left button: Switch between greyscale and rainbow RGB565 colour schemes
- Right button: If simulation is running, toggles drawing particle spawns and particle count

Planned Features
---

- Add alternative seed configurations, e.g. straight line at the bottom
- Investigate algorithms to accurately measure tree size (min and max radius)
- Investigate options for different spawn positions, as a function of tree size
- Add a 'gravity' force that attracts particles towards the centre of mass

Note that drawing the trails of the particles slows down the simulation a lot and doesn't seem worthwhile.

The speed of simulation is *monumentally* increased by not drawing empty cells!
