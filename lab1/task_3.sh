#! /bin/bash
function reverse {
	tac $1 | rev >$2
}
