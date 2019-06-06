void
gaplessgrid(Monitor *m) {
	unsigned int n, cols, rows, cn, rn, i, cx, cy, cw, ch, ww, wh;
	Client *c;

	ww = m->ww - m->gappx;
	wh = m->wh - m->gappx;

	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++) ;
	if(n == 0)
		return;

	/* grid dimensions */
	for(cols = 0; cols <= n/2; cols++)
		if(cols*cols >= n)
			break;
	if(n == 5) /* set layout against the general calculation: not 1:2:2, but 2:3 */
		cols = 2;
	rows = n/cols;

	/* window geometries */
	cw = cols ? ww / cols : ww;
	cn = 0; /* current column number */
	rn = 0; /* current row number */
	for(i = 0, c = nexttiled(m->clients); c; i++, c = nexttiled(c->next)) {
		if(i/rows + 1 > cols - n%cols)
			rows = n/cols + 1;
		ch = rows ? wh / rows : wh;
		cx = m->wx + cn*cw;
		cy = m->wy + rn*ch;
		resize(c, cx + m->gappx, cy + m->gappx, cw - 2 * c->bw - m->gappx, ch - 2 * c->bw - m->gappx, False);
		rn++;
		if(rn >= rows) {
			rn = 0;
			cn++;
		}
	}
}
