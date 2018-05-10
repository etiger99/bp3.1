(function() {
	var h = {},
	mt = {},
	c = {
		id: "c49232a8be82d37340e295f04cb9cf85",
		dm: ["openedv.com"],
		js: "tongji.baidu.com/hm-web/js/",
		etrk: [],
		icon: '',
		ctrk: false,
		align: -1,
		nv: -1,
		vdur: 1800000,
		age: 31536000000,
		rec: 0,
		rp: [],
		trust: 0,
		vcard: 0,
		qiao: 0,
		lxb: 0,
		conv: 0,
		apps: ''
	};
	var p = !0,
	s = null,
	t = !1;
	mt.g = {};
	mt.g.xa = /msie (\d+\.\d+)/i.test(navigator.userAgent);
	mt.g.cookieEnabled = navigator.cookieEnabled;
	mt.g.javaEnabled = navigator.javaEnabled();
	mt.g.language = navigator.language || navigator.browserLanguage || navigator.systemLanguage || navigator.userLanguage || "";
	mt.g.ia = (window.screen.width || 0) + "x" + (window.screen.height || 0);
	mt.g.colorDepth = window.screen.colorDepth || 0;
	mt.cookie = {};
	mt.cookie.set = function(a, b, f) {
		var d;
		f.z && (d = new Date, d.setTime(d.getTime() + f.z));
		document.cookie = a + "=" + b + (f.domain ? "; domain=" + f.domain: "") + (f.path ? "; path=" + f.path: "") + (d ? "; expires=" + d.toGMTString() : "") + (f.Ba ? "; secure": "")
	};
	mt.cookie.get = function(a) {
		return (a = RegExp("(^| )" + a + "=([^;]*)(;|$)").exec(document.cookie)) ? a[2] : s
	};
	mt.event = {};
	mt.event.e = function(a, b, f) {
		a.attachEvent ? a.attachEvent("on" + b,
		function(d) {
			f.call(a, d)
		}) : a.addEventListener && a.addEventListener(b, f, t)
	};
	mt.event.preventDefault = function(a) {
		a.preventDefault ? a.preventDefault() : a.returnValue = t
	};
	mt.m = {};
	mt.m.parse = function() {
		return (new Function('return (" + source + ")'))()
	};
	mt.m.stringify = function() {
		function a(a) { / ["\\\x00-\x1f]/.test(a)&&(a=a.replace(/["\\\x00 - \x1f] / g,
			function(a) {
				var b = f[a];
				if (b) return b;
				b = a.charCodeAt();
				return "\\u00" + Math.floor(b / 16).toString(16) + (b % 16).toString(16)
			}));
			return '"' + a + '"'
		}
		function b(a) {
			return 10 > a ? "0" + a: a
		}
		var f = {
			"\b": "\\b",
			"\t": "\\t",
			"\n": "\\n",
			"\f": "\\f",
			"\r": "\\r",
			'"': '\\"',
			"\\": "\\\\"
		};
		return function(d) {
			switch (typeof d) {
			case "undefined":
				return "undefined";
			case "number":
				return isFinite(d) ? String(d) : "null";
			case "string":
				return a(d);
			case "boolean":
				return String(d);
			default:
				if (d === s) return "null";
				if (d instanceof Array) {
					var f = ["["],
					n = d.length,
					l,
					e,
					m;
					for (e = 0; e < n; e++) switch (m = d[e], typeof m) {
					case "undefined":
					case "function":
					case "unknown":
						break;
					default:
						l && f.push(","),
						f.push(mt.m.stringify(m)),
						l = 1
					}
					f.push("]");
					return f.join("")
				}
				if (d instanceof Date) return '"' + d.getFullYear() + "-" + b(d.getMonth() + 1) + "-" + b(d.getDate()) + "T" + b(d.getHours()) + ":" + b(d.getMinutes()) + ":" + b(d.getSeconds()) + '"';
				l = ["{"];
				e = mt.m.stringify;
				for (n in d) if (Object.prototype.hasOwnProperty.call(d, n)) switch (m = d[n], typeof m) {
				case "undefined":
				case "unknown":
				case "function":
					break;
				default:
					f && l.push(","),
					f = 1,
					l.push(e(n) + ":" + e(m))
				}
				l.push("}");
				return l.join("")
			}
		}
	} ();
	mt.lang = {};
	mt.lang.d = function(a, b) {
		return "[object " + b + "]" === {}.toString.call(a)
	};
	mt.lang.ya = function(a) {
		return mt.lang.d(a, "Number") && isFinite(a)
	};
	mt.lang.Aa = function(a) {
		return mt.lang.d(a, "String")
	};
	mt.localStorage = {};
	mt.localStorage.s = function() {
		if (!mt.localStorage.f) try {
			mt.localStorage.f = document.createElement("input"),
			mt.localStorage.f.type = "hidden",
			mt.localStorage.f.style.display = "none",
			mt.localStorage.f.addBehavior("#default#userData"),
			document.getElementsByTagName("head")[0].appendChild(mt.localStorage.f)
		} catch(a) {
			return t
		}
		return p
	};
	mt.localStorage.set = function(a, b, f) {
		var d = new Date;
		d.setTime(d.getTime() + f || 31536E6);
		try {
			window.localStorage ? (b = d.getTime() + "|" + b, window.localStorage.setItem(a, b)) : mt.localStorage.s() && (mt.localStorage.f.expires = d.toUTCString(), mt.localStorage.f.load(document.location.hostname), mt.localStorage.f.setAttribute(a, b), mt.localStorage.f.save(document.location.hostname))
		} catch(g) {}
	};
	mt.localStorage.get = function(a) {
		if (window.localStorage) {
			if (a = window.localStorage.getItem(a)) {
				var b = a.indexOf("|"),
				f = a.substring(0, b) - 0;
				if (f && f > (new Date).getTime()) return a.substring(b + 1)
			}
		} else if (mt.localStorage.s()) try {
			return mt.localStorage.f.load(document.location.hostname),
			mt.localStorage.f.getAttribute(a)
		} catch(d) {}
		return s
	};
	mt.localStorage.remove = function(a) {
		if (window.localStorage) window.localStorage.removeItem(a);
		else if (mt.localStorage.s()) try {
			mt.localStorage.f.load(document.location.hostname),
			mt.localStorage.f.removeAttribute(a),
			mt.localStorage.f.save(document.location.hostname)
		} catch(b) {}
	};
	mt.sessionStorage = {};
	mt.sessionStorage.set = function(a, b) {
		if (window.sessionStorage) try {
			window.sessionStorage.setItem(a, b)
		} catch(f) {}
	};
	mt.sessionStorage.get = function(a) {
		return window.sessionStorage ? window.sessionStorage.getItem(a) : s
	};
	mt.sessionStorage.remove = function(a) {
		window.sessionStorage && window.sessionStorage.removeItem(a)
	};
	mt.G = {};
	mt.G.log = function(a, b) {
		var f = new Image,
		d = "mini_tangram_log_" + Math.floor(2147483648 * Math.random()).toString(36);
		window[d] = f;
		f.onload = f.onerror = f.onabort = function() {
			f.onload = f.onerror = f.onabort = s;
			f = window[d] = s;
			b && b(a)
		};
		f.src = a
	};
	mt.H = {};
	mt.H.ba = function() {
		var a = "";
		if (navigator.plugins && navigator.mimeTypes.length) {
			var b = navigator.plugins["Shockwave Flash"];
			b && b.description && (a = b.description.replace(/^.*\s+(\S+)\s+\S+$/, "$1"))
		} else if (window.ActiveXObject) try {
			if (b = new ActiveXObject("ShockwaveFlash.ShockwaveFlash"))(a = b.GetVariable("$version")) && (a = a.replace(/^.*\s+(\d+),(\d+).*$/, "$1.$2"))
		} catch(f) {}
		return a
	};
	mt.H.ta = function(a, b, f, d, g) {
		return '<object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" id="' + a + '" width="' + f + '" height="' + d + '"><param name="movie" value="' + b + '" /><param name="flashvars" value="' + (g || "") + '" /><param name="allowscriptaccess" value="always" /><embed type="application/x-shockwave-flash" name="' + a + '" width="' + f + '" height="' + d + '" src="' + b + '" flashvars="' + (g || "") + '" allowscriptaccess="always" /></object>'
	};
	mt.url = {};
	mt.url.k = function(a, b) {
		var f = a.match(RegExp("(^|&|\\?|#)(" + b + ")=([^&#]*)(&|$|#)", ""));
		return f ? f[3] : s
	};
	mt.url.va = function(a) {
		return (a = a.match(/^(https?:)\/\//)) ? a[1] : s
	};
	mt.url.Z = function(a) {
		return (a = a.match(/^(https?:\/\/)?([^\/\?#]*)/)) ? a[2].replace(/.*@/, "") : s
	};
	mt.url.K = function(a) {
		return (a = mt.url.Z(a)) ? a.replace(/:\d+$/, "") : a
	};
	mt.url.ua = function(a) {
		return (a = a.match(/^(https?:\/\/)?[^\/]*(.*)/)) ? a[2].replace(/[\?#].*/, "").replace(/^$/, "/") : s
	};
	h.I = {
		wa: "http://tongji.baidu.com/hm-web/welcome/ico",
		P: "hm.baidu.com/hm.gif",
		S: "baidu.com",
		ea: "hmmd",
		fa: "hmpl",
		da: "hmkw",
		ca: "hmci",
		ga: "hmsr",
		l: 0,
		h: Math.round( + new Date / 1E3),
		protocol: "https:" == document.location.protocol ? "https:": "http:",
		za: 0,
		qa: 6E5,
		ra: 10,
		sa: 1024,
		pa: 1,
		q: 2147483647,
		Q: "cc cf ci ck cl cm cp cw ds ep et fl ja ln lo lt nv rnd si st su v cv lv api tt u".split(" ")
	}; (function() {
		var a = {
			i: {},
			e: function(a, f) {
				this.i[a] = this.i[a] || [];
				this.i[a].push(f)
			},
			o: function(a, f) {
				this.i[a] = this.i[a] || [];
				for (var d = this.i[a].length, g = 0; g < d; g++) this.i[a][g](f)
			}
		};
		return h.w = a
	})(); (function() {
		function a(a, d) {
			var g = document.createElement("script");
			g.charset = "utf-8";
			b.d(d, "Function") && (g.readyState ? g.onreadystatechange = function() {
				if ("loaded" === g.readyState || "complete" === g.readyState) g.onreadystatechange = s,
				d()
			}: g.onload = function() {
				d()
			});
			g.src = a;
			var n = document.getElementsByTagName("script")[0];
			n.parentNode.insertBefore(g, n)
		}
		var b = mt.lang;
		return h.load = a
	})(); (function() {
		function a() {
			return function() {
				h.b.a.nv = 0;
				h.b.a.st = 4;
				h.b.a.et = 3;
				h.b.a.ep = h.t.$() + "," + h.t.Y();
				h.b.j()
			}
		}
		function b() {
			clearTimeout(x);
			var a;
			w && (a = "visible" == document[w]);
			y && (a = !document[y]);
			e = "undefined" == typeof a ? p: a;
			if ((!l || !m) && e && k) u = p,
			r = +new Date;
			else if (l && m && (!e || !k)) u = t,
			q += +new Date - r;
			l = e;
			m = k;
			x = setTimeout(b, 100)
		}
		function f(a) {
			var m = document,
			r = "";
			if (a in m) r = a;
			else for (var q = ["webkit", "ms", "moz", "o"], b = 0; b < q.length; b++) {
				var k = q[b] + a.charAt(0).toUpperCase() + a.slice(1);
				if (k in m) {
					r = k;
					break
				}
			}
			return r
		}
		function d(a) {
			if (! ("focus" == a.type || "blur" == a.type) || !(a.target && a.target != window)) k = "focus" == a.type || "focusin" == a.type ? p: t,
			b()
		}
		var g = mt.event,
		n = h.w,
		l = p,
		e = p,
		m = p,
		k = p,
		v = +new Date,
		r = v,
		q = 0,
		u = p,
		w = f("visibilityState"),
		y = f("hidden"),
		x;
		b(); (function() {
			var a = w.replace(/[vV]isibilityState/, "visibilitychange");
			g.e(document, a, b);
			g.e(window, "pageshow", b);
			g.e(window, "pagehide", b);
			"object" == typeof document.onfocusin ? (g.e(document, "focusin", d), g.e(document, "focusout", d)) : (g.e(window, "focus", d), g.e(window, "blur", d))
		})();
		h.t = {
			$: function() {
				return + new Date - v
			},
			Y: function() {
				return u ? +new Date - r + q: q
			}
		};
		n.e("pv-b",
		function() {
			g.e(window, "unload", a())
		});
		return h.t
	})(); (function() {
		function a(m) {
			for (var b in m) if ({}.hasOwnProperty.call(m, b)) {
				var e = m[b];
				d.d(e, "Object") || d.d(e, "Array") ? a(e) : m[b] = String(e)
			}
		}
		function b(a) {
			return a.replace ? a.replace(/'/g, "'0").replace(/\*/g, "'1").replace(/!/g, "'2") : a
		}
		var f = mt.G,
		d = mt.lang,
		g = mt.m,
		n = h.I,
		l = h.w,
		e = {
			L: s,
			n: [],
			r: 0,
			M: t,
			init: function() {
				e.c = 0;
				e.L = {
					push: function() {
						e.D.apply(e, arguments)
					}
				};
				l.e("pv-b",
				function() {
					e.V();
					e.W()
				});
				l.e("pv-d", e.X);
				l.e("stag-b",
				function() {
					h.b.a.api = e.c || e.r ? e.c + "_" + e.r: ""
				});
				l.e("stag-d",
				function() {
					h.b.a.api = 0;
					e.c = 0;
					e.r = 0
				})
			},
			V: function() {
				var a = window._hmt;
				if (a && a.length) for (var b = 0; b < a.length; b++) {
					var d = a[b];
					switch (d[0]) {
					case "_setAccount":
						1 < d.length && /^[0-9a-z]{32}$/.test(d[1]) && (e.c |= 1, window._bdhm_account = d[1]);
						break;
					case "_setAutoPageview":
						if (1 < d.length && (d = d[1], t === d || p === d)) e.c |= 2,
						window._bdhm_autoPageview = d
					}
				}
			},
			W: function() {
				if ("undefined" === typeof window._bdhm_account || window._bdhm_account === c.id) {
					window._bdhm_account = c.id;
					var a = window._hmt;
					if (a && a.length) for (var b = 0,
					f = a.length; b < f; b++) d.d(a[b], "Array") && "_trackEvent" !== a[b][0] && "_trackRTEvent" !== a[b][0] ? e.D(a[b]) : e.n.push(a[b]);
					window._hmt = e.L
				}
			},
			X: function() {
				if (0 < e.n.length) for (var a = 0,
				b = e.n.length; a < b; a++) e.D(e.n[a]);
				e.n = s
			},
			D: function(a) {
				if (d.d(a, "Array")) {
					var b = a[0];
					if (e.hasOwnProperty(b) && d.d(e[b], "Function")) e[b](a)
				}
			},
			_trackPageview: function(a) {
				if (1 < a.length && a[1].charAt && "/" == a[1].charAt(0)) {
					e.c |= 4;
					h.b.a.et = 0;
					h.b.a.ep = "";
					h.b.B ? (h.b.a.nv = 0, h.b.a.st = 4) : h.b.B = p;
					var b = h.b.a.u,
					d = h.b.a.su;
					h.b.a.u = n.protocol + "//" + document.location.host + a[1];
					e.M || (h.b.a.su = document.location.href);
					h.b.j();
					h.b.a.u = b;
					h.b.a.su = d
				}
			},
			_trackEvent: function(a) {
				2 < a.length && (e.c |= 8, h.b.a.nv = 0, h.b.a.st = 4, h.b.a.et = 4, h.b.a.ep = b(a[1]) + "*" + b(a[2]) + (a[3] ? "*" + b(a[3]) : "") + (a[4] ? "*" + b(a[4]) : ""), h.b.j())
			},
			_setCustomVar: function(a) {
				if (! (4 > a.length)) {
					var d = a[1],
					f = a[4] || 3;
					if (0 < d && 6 > d && 0 < f && 4 > f) {
						e.r++;
						for (var r = (h.b.a.cv || "*").split("!"), q = r.length; q < d - 1; q++) r.push("*");
						r[d - 1] = f + "*" + b(a[2]) + "*" + b(a[3]);
						h.b.a.cv = r.join("!");
						a = h.b.a.cv.replace(/[^1](\*[^!]*){2}/g, "*").replace(/((^|!)\*)+$/g, "");
						"" !== a ? h.b.setData("Hm_cv_" + c.id, encodeURIComponent(a), c.age) : h.b.ha("Hm_cv_" + c.id)
					}
				}
			},
			_setReferrerOverride: function(a) {
				1 < a.length && (h.b.a.su = a[1].charAt && "/" == a[1].charAt(0) ? n.protocol + "//" + window.location.host + a[1] : a[1], e.M = p)
			},
			_trackOrder: function(b) {
				b = b[1];
				d.d(b, "Object") && (a(b), e.c |= 16, h.b.a.nv = 0, h.b.a.st = 4, h.b.a.et = 94, h.b.a.ep = g.stringify(b), h.b.j())
			},
			_trackMobConv: function(a) {
				if (a = {
					webim: 1,
					tel: 2,
					map: 3,
					sms: 4,
					callback: 5,
					share: 6
				} [a[1]]) e.c |= 32,
				h.b.a.et = 93,
				h.b.a.ep = a,
				h.b.j()
			},
			_trackRTPageview: function(b) {
				b = b[1];
				d.d(b, "Object") && (a(b), b = g.stringify(b), 512 >= encodeURIComponent(b).length && (e.c |= 64, h.b.a.rt = b))
			},
			_trackRTEvent: function(b) {
				b = b[1];
				if (d.d(b, "Object")) {
					a(b);
					b = encodeURIComponent(g.stringify(b));
					var f = function(a) {
						var b = h.b.a.rt;
						e.c |= 128;
						h.b.a.et = 90;
						h.b.a.rt = a;
						h.b.j();
						h.b.a.rt = b
					},
					l = b.length;
					if (900 >= l) f.call(this, b);
					else for (var l = Math.ceil(l / 900), r = "block|" + Math.round(Math.random() * n.q).toString(16) + "|" + l + "|", q = [], u = 0; u < l; u++) q.push(u),
					q.push(b.substring(900 * u, 900 * u + 900)),
					f.call(this, r + q.join("|")),
					q = []
				}
			},
			_setUserId: function(a) {
				a = a[1];
				if (d.d(a, "String") || d.d(a, "Number")) {
					var b = h.b.A(),
					g = "hm-" + h.b.a.v;
					e.O = e.O || Math.round(Math.random() * n.q);
					f.log("//datax.baidu.com/x.gif?si=" + c.id + "&dm=" + encodeURIComponent(b) + "&ac=" + encodeURIComponent(a) + "&v=" + g + "&li=" + e.O + "&rnd=" + Math.round(Math.random() * n.q))
				}
			}
		};
		e.init();
		h.T = e;
		return h.T
	})(); (function() {
		function a() {
			"undefined" == typeof window["_bdhm_loaded_" + c.id] && (window["_bdhm_loaded_" + c.id] = p, this.a = {},
			this.B = t, this.init())
		}
		var b = mt.url,
		f = mt.G,
		d = mt.H,
		g = mt.lang,
		n = mt.cookie,
		l = mt.g,
		e = mt.localStorage,
		m = mt.sessionStorage,
		k = h.I,
		v = h.w;
		a.prototype = {
			C: function(a, b) {
				a = "." + a.replace(/:\d+/, "");
				b = "." + b.replace(/:\d+/, "");
				var d = a.indexOf(b);
				return - 1 < d && d + b.length == a.length
			},
			N: function(a, b) {
				a = a.replace(/^https?:\/\//, "");
				return 0 === a.indexOf(b)
			},
			p: function(a) {
				for (var d = 0; d < c.dm.length; d++) if ( - 1 < c.dm[d].indexOf("/")) {
					if (this.N(a, c.dm[d])) return p
				} else {
					var e = b.K(a);
					if (e && this.C(e, c.dm[d])) return p
				}
				return t
			},
			A: function() {
				for (var a = document.location.hostname,
				b = 0,
				d = c.dm.length; b < d; b++) if (this.C(a, c.dm[b])) return c.dm[b].replace(/(:\d+)?[\/\?#].*/, "");
				return a
			},
			J: function() {
				for (var a = 0,
				b = c.dm.length; a < b; a++) {
					var d = c.dm[a];
					if ( - 1 < d.indexOf("/") && this.N(document.location.href, d)) return d.replace(/^[^\/]+(\/.*)/, "$1") + "/"
				}
				return "/"
			},
			aa: function() {
				if (!document.referrer) return k.h - k.l > c.vdur ? 1 : 4;
				var a = t;
				this.p(document.referrer) && this.p(document.location.href) ? a = p: (a = b.K(document.referrer), a = this.C(a || "", document.location.hostname));
				return a ? k.h - k.l > c.vdur ? 1 : 4 : 3
			},
			getData: function(a) {
				try {
					return n.get(a) || m.get(a) || e.get(a)
				} catch(b) {}
			},
			setData: function(a, b, d) {
				try {
					n.set(a, b, {
						domain: this.A(),
						path: this.J(),
						z: d
					}),
					d ? e.set(a, b, d) : m.set(a, b)
				} catch(f) {}
			},
			ha: function(a) {
				try {
					n.set(a, "", {
						domain: this.A(),
						path: this.J(),
						z: -1
					}),
					m.remove(a),
					e.remove(a)
				} catch(b) {}
			},
			na: function() {
				var a, b, d, e, f;
				k.l = this.getData("Hm_lpvt_" + c.id) || 0;
				13 == k.l.length && (k.l = Math.round(k.l / 1E3));
				b = this.aa();
				a = 4 != b ? 1 : 0;
				if (d = this.getData("Hm_lvt_" + c.id)) {
					e = d.split(",");
					for (f = e.length - 1; 0 <= f; f--) 13 == e[f].length && (e[f] = "" + Math.round(e[f] / 1E3));
					for (; 2592E3 < k.h - e[0];) e.shift();
					f = 4 > e.length ? 2 : 3;
					for (1 === a && e.push(k.h); 4 < e.length;) e.shift();
					d = e.join(",");
					e = e[e.length - 1]
				} else d = k.h,
				e = "",
				f = 1;
				this.setData("Hm_lvt_" + c.id, d, c.age);
				this.setData("Hm_lpvt_" + c.id, k.h);
				d = k.h == this.getData("Hm_lpvt_" + c.id) ? "1": "0";
				if (0 === c.nv && this.p(document.location.href) && ("" === document.referrer || this.p(document.referrer))) a = 0,
				b = 4;
				this.a.nv = a;
				this.a.st = b;
				this.a.cc = d;
				this.a.lt = e;
				this.a.lv = f
			},
			ma: function() {
				for (var a = [], b = 0, d = k.Q.length; b < d; b++) {
					var e = k.Q[b],
					f = this.a[e];
					"undefined" != typeof f && "" !== f && a.push(e + "=" + encodeURIComponent(f))
				}
				b = this.a.et;
				this.a.rt && (0 === b ? a.push("rt=" + encodeURIComponent(this.a.rt)) : 90 === b && a.push("rt=" + this.a.rt));
				return a.join("&")
			},
			oa: function() {
				this.na();
				this.a.si = c.id;
				this.a.su = document.referrer;
				this.a.ds = l.ia;
				this.a.cl = l.colorDepth + "-bit";
				this.a.ln = l.language;
				this.a.ja = l.javaEnabled ? 1 : 0;
				this.a.ck = l.cookieEnabled ? 1 : 0;
				this.a.lo = "number" == typeof _bdhm_top ? 1 : 0;
				this.a.fl = d.ba();
				this.a.v = "1.0.75";
				this.a.cv = decodeURIComponent(this.getData("Hm_cv_" + c.id) || "");
				1 == this.a.nv && (this.a.tt = document.title || "");
				var a = document.location.href;
				this.a.cm = b.k(a, k.ea) || "";
				this.a.cp = b.k(a, k.fa) || "";
				this.a.cw = b.k(a, k.da) || "";
				this.a.ci = b.k(a, k.ca) || "";
				this.a.cf = b.k(a, k.ga) || ""
			},
			init: function() {
				try {
					this.oa(),
					0 === this.a.nv ? this.la() : this.F(".*"),
					h.b = this,
					this.U(),
					v.o("pv-b"),
					this.ka()
				} catch(a) {
					var b = [];
					b.push("si=" + c.id);
					b.push("n=" + encodeURIComponent(a.name));
					b.push("m=" + encodeURIComponent(a.message));
					b.push("r=" + encodeURIComponent(document.referrer));
					f.log(k.protocol + "//" + k.P + "?" + b.join("&"))
				}
			},
			ka: function() {
				function a() {
					v.o("pv-d")
				}
				"undefined" === typeof window._bdhm_autoPageview || window._bdhm_autoPageview === p ? (this.B = p, this.a.et = 0, this.a.ep = "", this.j(a)) : a()
			},
			j: function(a) {
				var b = this;
				b.a.rnd = Math.round(Math.random() * k.q);
				v.o("stag-b");
				var d = k.protocol + "//" + k.P + "?" + b.ma();
				v.o("stag-d");
				b.R(d);
				f.log(d,
				function(d) {
					b.F(d);
					g.d(a, "Function") && a.call(b)
				})
			},
			U: function() {
				var a = document.location.hash.substring(1),
				d = RegExp(c.id),
				e = -1 < document.referrer.indexOf(k.S) ? p: t,
				f = b.k(a, "jn"),
				g = /^heatlink$|^select$/.test(f);
				a && (d.test(a) && e && g) && (a = document.createElement("script"), a.setAttribute("type", "text/javascript"), a.setAttribute("charset", "utf-8"), a.setAttribute("src", k.protocol + "//" + c.js + f + ".js?" + this.a.rnd), f = document.getElementsByTagName("script")[0], f.parentNode.insertBefore(a, f))
			},
			R: function(a) {
				var b = m.get("Hm_unsent_" + c.id) || "",
				d = this.a.u ? "": "&u=" + encodeURIComponent(document.location.href),
				b = encodeURIComponent(a.replace(/^https?:\/\//, "") + d) + (b ? "," + b: "");
				m.set("Hm_unsent_" + c.id, b)
			},
			F: function(a) {
				var b = m.get("Hm_unsent_" + c.id) || "";
				b && ((b = b.replace(RegExp(encodeURIComponent(a.replace(/^https?:\/\//, "")).replace(/([\*\(\)])/g, "\\$1") + "(%26u%3D[^,]*)?,?", "g"), "").replace(/,$/, "")) ? m.set("Hm_unsent_" + c.id, b) : m.remove("Hm_unsent_" + c.id))
			},
			la: function() {
				var a = this,
				b = m.get("Hm_unsent_" + c.id);
				if (b) for (var b = b.split(","), d = function(b) {
					f.log(k.protocol + "//" + decodeURIComponent(b).replace(/^https?:\/\//, ""),
					function(b) {
						a.F(b)
					})
				},
				e = 0, g = b.length; e < g; e++) d(b[e])
			}
		};
		return new a
	})();
})();