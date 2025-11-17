Diffusion-limited aggregation (DLA) simulation
===

Simulate randomly walking particles and growth of Brownian trees on the T-Display S3.

Inspirations and References
---

- Project initially inspired by [this Youtube video](https://www.youtube.com/watch?v=gsJHzBTPG0Y) about procedural mountain generation.
- See the [Wikipedia article on DLA](https://en.wikipedia.org/wiki/Diffusion-limited_aggregation) for more details.
- There are some excellent animations on [this page about cellular automata](https://robotmoon.com/cellular-automata/#elementary-cellular-automata).

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

1. Test out various colour palettes and ways of storing particle lifetime
2. Add alternative seed configurations, e.g. straight line at the bottom
3. Implement an algorithm to accurately measure tree size (min and max radius)
4. Implement better algorithms for random spawn position as a function of tree size
5. Add a 'gravity' force that attracts particles towards the centre of mass

Note that drawing the trails of the particles slows down the simulation a lot and doesn't seem worthwhile.

The speed of simulation is *monumentally* increased by not drawing empty cells!
