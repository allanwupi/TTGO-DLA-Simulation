Diffusion-limited aggregation (DLA) simulation
===

Simulate randomly walking particles and growth of Brownian trees on the T-Display S3.

Initially inspired by [this Youtube video](https://www.youtube.com/watch?v=gsJHzBTPG0Y) about procedural mountain generation. See the [Wikipedia article on DLA](https://en.wikipedia.org/wiki/Diffusion-limited_aggregation) for more details.

Current Implementation
---

1. Seed is placed at the centre of the screen
2. Particle spawned at a random angle, initial circular radius 3
3. Walk particle randomly until it sticks to the seed (Moore neighbourhood)
4. Repeat with a new particle - increase spawn radius as needed

Limitations and Planned Features
---

The current simulation is _very_ slow. Also, it could look a lot prettier.

There are some excellent animations on [this page about cellular automata](https://robotmoon.com/cellular-automata/#elementary-cellular-automata).

1. Implement a better algorithm for spawn positions as a function of tree size
2. Add alternative seed configurations, e.g. straight line at the bottom
3. Add a 'gravity' force that attracts particles towards the centre of mass
4. Support multiple particles moving about simultaneously
5. Draw decaying trails to show the Brownian motion of the particles
6. Make a colour palette for particles based on simulation time
