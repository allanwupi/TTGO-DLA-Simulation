Diffusion-limited aggregation (DLA) simulation
===

Simulate randomly walking particles and growth of Brownian trees using the LILYGO T-Display S3.

See the information at [rosettacode.org](https://rosettacode.org/wiki/Brownian_tree) and the [Wikipedia article](https://en.wikipedia.org/wiki/Diffusion-limited_aggregation).

Current Implementation
---

1. Seed is placed at the centre of the screen
2. Particle spawned at a random angle, initial circular radius 3
3. Walk particle randomly until it sticks to the seed (Moore neighbourhood)
4. Repeat with a new particle - increase spawn radius as needed

Limitations and Planned Features
---

The current simulation is very, _very_ slow. Also, it could look a bit prettier.

1. Add alternative seed configurations, e.g. straight line at the bottom
2. Add a 'gravity' force that attracts particles towards the centre
3. Support multiple particles moving about simultaneously
4. Draw decaying trails to show the Brownian motion of the particles
5. Make a colour palette for particles based on simulation time
6. Rescale screen dynamically as the size of the tree increases
