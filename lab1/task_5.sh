#! /bin/bash
function Exit {
	([[ $# -eq 0 ]] && exit 0 || exit $1)
}
