Diffusion-limited aggregation (DLA) simulation
===

Simulate randomly walking particles and growth of Brownian trees on the T-Display S3.

Initially inspired by [this Youtube video](https://www.youtube.com/watch?v=gsJHzBTPG0Y) about procedural mountain generation. See the [Wikipedia article on DLA](https://en.wikipedia.org/wiki/Diffusion-limited_aggregation) for more details.

![Example Brownian tree.](https://github.com/allanwupi/TTGO-DLA-Simulation/blob/main/img/IMG_0146.jpg)

Current Implementation
---

1. Place seed at the centre of the screen
2. Spawn particle on circular perimeter: random angle and initial radius 3
3. Walk particle randomly until it sticks to the seed (Moore neighbourhood)
4. Respawn particle and repeat - increase spawn circle radius when necessary
5. Once circle radius exceeds screen width, spawn randomly outside radius instead

Limitations and Planned Features
---

The current simulation is _very_ slow. Also, it could look a lot prettier.

There are some excellent animations on [this page about cellular automata](https://robotmoon.com/cellular-automata/#elementary-cellular-automata).

1. Implement a better algorithm for spawn positions as a function of tree size
2. Add alternative seed configurations, e.g. straight line at the bottom
3. Add a 'gravity' force that attracts particles towards the centre of mass
4. Support multiple particles moving about simultaneously
5. Test out various colour palettes and ways of storing particle lifetime

Note: drawing the trails of the particles slows down the simulation much more and doesn't seem worthwhile.
